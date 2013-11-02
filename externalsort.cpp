/*
Author: Aditya Rastogi
Date : 17/07/2012

*/
#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<cstdio>
#include<exception>
#include<cstdlib>
#include<sstream>
#define EXCEPT(x,y) if((x)==(y)) throw new std::exception();
#define INBUF_EMPTY 1
#define OUTBUF_FULL 2
#define FILE_BUF_SIZE 10000
#define REC_SEP '\n'

/* a generic implementation of the external merge sort algorithm. The class encaplsulates
this functionality via templates for different datatypes, for the sort to work , the following 
are required:

1. A input data file where records of type <T> are separated by newline char and each record
<r> itself does not contain the newline char
2. A functor object that defines the < operator(strict weak ordering) on the objects of type <T>
3. Overloaded << and >> operators for the onject of type <T>

The pperoformance of the sort can be tweaked by changing the buffer size (in bytes) and FILE_BUF_SIZE (in bytes)
values where the buffer is the in memory buffer(which stores values and sorts them) size and FILE_BUF_SIZE is the 
buffer size for file reads*/


template<typename T, class functor>
class ExternalSort{

	private:

		/*data members to keep track of the algorithm state*/	
		T* buffer;				//buffer for in-memory sorting.	
		size_t data_size;		//data file size in bytes.
		size_t bufsize;			//buffer size in bytes.
		int num_elems;			//number of elements of type T in buffer.
		functor compareFunc;	//compare function for the input data.
		char* inputfile;		//input file name.
		char* outputfile;		//output file name.
		bool keepTempFiles;		//whether to keep the temp files generated

		/*structure to hold info about temp file buffers.*/
		struct filebuffer{      
			T* fbhead;				//pointer to buffer head for this file inside T* buffer;
			char fname[L_tmpnam];	//name of temporary file.
			int fbsize;				//size of buffer.
			std::fstream fbhandle;	//file handle to the temp file.

			
			/*copying function for efficient copying of stream obects in heap*/
			void makeCopy(const filebuffer& f){

				fbhead = f.fbhead;
				std::strcpy(fname,f.fname);
				fbsize = f.fbsize;
				//copy the stream
				fbhandle.copyfmt(f.fbhandle);
				fbhandle.clear(f.fbhandle.rdstate());
				fbhandle.std::basic_ios<char>::rdbuf(f.fbhandle.std::basic_ios<char>::rdbuf());
			}

			/*constructors*/
			public:
			filebuffer(){};
			filebuffer(const filebuffer& f){
				makeCopy(f);
			};

			/*overloaded equal to for assignment*/
			filebuffer& operator=(filebuffer& f){
				if(this!=&f)
					makeCopy(f);
				return *this;

			}

			/*destructor*/
			~filebuffer(){
				/*close all the file handles*/
				fbhandle.close();
			}

			
		}
		*fbtable;				//table to store the temp file buffer information.
		int ftsize;				//size of temp file info table.

		/*comparison function to compare buffer heads, for a min heap , empty bufheads are treated as max keys, returns a>b.*/
		class compFbuf{
		public: bool operator()(filebuffer& f1,filebuffer& f2){
				bool res=false;
				if(f1.fbsize == 0 && f2.fbsize > 0) return true;
				else if(f1.fbsize > 0 && f2.fbsize == 0) return false;
				else if (f1.fbsize > 0 && f2.fbsize > 0) return ((*(f1.fbhead)==*(f2.fbhead))?false:!(*(f1.fbhead) < *(f2.fbhead)));
				else return false;
			}
		};
		const compFbuf comparator;
		
		/*member functions*/

		/*create the initial sort files for the algorithm*/
		void makeSortFiles();
		/*writes a specified number size s elements to file*/
		void writeToFile(std::fstream& fout, T* bufhead, size_t size);
		/*reads a specified size s number of elements from a file or less if the file is exhausted*/
		int readFromFile(std::fstream& fin, T*& bufhead, size_t size);
		/*merges the buffers contained inside this::buffer*/
		int mergeBuffers();
		/*initialises the file buffer table*/
		void initFileBuffers() throw();
		
	
	public :

		/*the sort function*/
		void sort();
		
		/*constructor*/
		ExternalSort(char* ifile, char* ofile, bool tempKeep,  functor _compareFunc):
		   bufsize(1024),
		   inputfile(ifile),
		   outputfile(ofile),
		   keepTempFiles(tempKeep),
		   compareFunc(_compareFunc){
		
			   try{

				   /*calculate file size*/
				   std::fstream in(inputfile,std::ios::in|std::ios::binary);
				   EXCEPT(in,NULL);
				   in.seekg(0,std::ios::end);
				   data_size = (in.tellg());
				   in.close();
				   
				   /*initialize the struct to hold file handles, buffer pointers and size of each buffer with an approx estimate of ftsize*/
				   ftsize = (data_size/bufsize) + ((data_size%bufsize)?1:0);
				   fbtable = new filebuffer[ftsize+1];
				   EXCEPT(fbtable,NULL);

				   /*allocate the buffer memory*/
				   num_elems = bufsize/sizeof(T);
				   buffer = new T[num_elems];
				   EXCEPT(buffer,NULL);

			   }catch(std::exception e){
			    
			   }

		}

		/*destructor*/
		~ExternalSort(){

			/*if keeptempFiles is false then delete them*/
			if(!keepTempFiles)
				for(int i=0;i<ftsize;i++){
					fbtable[i].fbhandle.close();
					if(fbtable[i].fbhandle.is_open()) std::cout<<"file open";
					char* dir = "C:\\Users\\vsales\\Documents\\Visual Studio 2010\\Projects\\External_merge_sort\\External_merge_sort\\";
					char n[150];
					std::strcpy(n,dir);
					std::strcat(n,fbtable[i].fname);
					int x = std::remove(n);
					std::perror("Could not delete file:");
				}

			/*delete the file table*/
			delete[] fbtable;

			/*delete the buffer*/
			delete[] buffer;
			
		}

		
};


template<typename T,class functor>
int ExternalSort<T,functor>::readFromFile(std::fstream& fin, T*& bufhead, size_t size){

	/*optimized for fast Input by reading a large chunk of data into 
	memory at a time and then parsing it in memory to improve efficiency*/

	char rbuf[FILE_BUF_SIZE];
	
	size_t count = 0;
	
	try {
		while(count < size && fin){

			fin.read(rbuf,FILE_BUF_SIZE);
			int read=fin.gcount();
			int getptr = 0;

			/*truncate the trailing buffer to avoid incomplete data reads*/	
			int i;
			if(read<FILE_BUF_SIZE && rbuf[read-1]!=REC_SEP)
				/*file terminates without CRLF we need not move i*/
				i=0;						
			else {
				for(i=read-1;i>=0 && rbuf[i]!=REC_SEP;i--); 
				rbuf[i]=EOF;
			}
		
			std::stringstream formatter(rbuf,std::stringstream::in);
		
			while(count<size && formatter>>bufhead[count]){
				getptr = formatter.tellg();
				count++;
			}
			
			/*reset the file buffer for next read*/ 

			/*if the file ends in CR+LF or LF or without either*/
			if(((read-getptr)<=2 && rbuf[read-1]==EOF) || (read==getptr)); 
			else {
				/*otherwise EOF is not near, so continue reading by clearing the EOF*/
				fin.clear();												
				fin.seekg(-(read-getptr),std::ios::cur);
			}
		}
	}
	catch(...){
	
	}
	
	
	return count;
}

template<typename T,class functor>
void ExternalSort<T,functor>::writeToFile(std::fstream& fout, T* bufhead, size_t size){

	/*optimizing for fast writes by writing the data to a string buffer in memory first 
	and then flushing that buffer to file */
	
	size_t count=0;
	try {
			std::stringstream formatter;
			while(count<size){
				formatter << bufhead[count]<<std::endl;
				count++;
			}
			fout<<formatter.rdbuf();
	
	}
	catch(std::exception e){
	
	}
}

template<typename T, class functor>
void ExternalSort<T,functor>::makeSortFiles(){

	
	int k=0;
	
	/*open the inputfile*/
	std::fstream in(inputfile,std::ios::in|std::ios::binary);
	
	while(in){
	
		try{

			/*read file into buffer*/
			int len = readFromFile(in,buffer,num_elems);

			/*sort the buffer array*/
			std::sort(buffer,buffer+len,compareFunc);

			/*get temp file name */
			if(std::tmpnam(fbtable[k].fname)){
				std::strcat(fbtable[k].fname,"txt");
				fbtable[k].fname[0] = 't';
			}
					
			/*write to temp file*/
			std::fstream tempfp(fbtable[k].fname,std::ios::out);
			writeToFile(tempfp,buffer,len);
			tempfp.close();

		}catch(std::exception e){
			;
		}
		

		k++;
	}
	in.close();

	/*update the size for the file table*/
	ftsize=k;
}

template<typename T,class functor>
int ExternalSort<T,functor>::mergeBuffers(){
	
	
	/*get references to the minbuf and outbuf and make the heap*/
	filebuffer &minhead = fbtable[ftsize-1];
	filebuffer &outhead = fbtable[ftsize];
	

	while(1){

		if(outhead.fbsize !=0){
			/*get the smallest element for the buffer*/
			std::make_heap(fbtable,fbtable+ftsize,comparator);
			std::pop_heap(fbtable,fbtable+ftsize,comparator);
			if(minhead.fbsize !=0){
				*(outhead.fbhead) =  *(minhead.fbhead);
				outhead.fbhead++;
				minhead.fbhead++;
				outhead.fbsize--;
				minhead.fbsize--;
			}
		}/*stop merging if the out buffer is empty*/
		else return OUTBUF_FULL;
		/*stop merging if the in buffer is empty*/
		if(minhead.fbsize == 0)
			return INBUF_EMPTY;
	}
}

template<typename T,class functor>
void ExternalSort<T,functor>::initFileBuffers() throw(){

	
	/*calculate size for each filebuf*/ 
	int fbufsize = bufsize/((ftsize+1)*sizeof(T));


	/*set the file handle and bufhead for in buffers*/
	int i;
	for(i=0;i<ftsize;i++){
		fbtable[i].fbhandle.open(fbtable[i].fname,std::ios::in|std::ios::binary);
		EXCEPT(fbtable[i].fbhandle,NULL);
		fbtable[i].fbhead = buffer + (i * fbufsize);
		fbtable[i].fbsize = 0;
	}

	/*set the file handle and bufhead for out buffer*/
	fbtable[i].fbhead = buffer + (i*fbufsize);
	fbtable[i].fbsize = fbufsize;
	strcpy(fbtable[i].fname,outputfile);
	fbtable[i].fbhandle.open(fbtable[i].fname,std::ios::out);
	EXCEPT(fbtable[i].fbhandle,NULL);
	strcpy(fbtable[ftsize].fname,outputfile);

}

template<typename T,class functor>
void ExternalSort<T,functor>::sort(){

	
	

	/*get the file table for the sort files*/
	makeSortFiles();

	/*initialise the markers for the minbuf and outbuf*/
	int MINBUF = ftsize-1; 
	int OUTBUF = ftsize;

	try {
		
		/*with output buffer, divide into ftsize+1 number of buffers*/
		int fbufsize = bufsize/((ftsize+1)*sizeof(T));

		/*open the file handles and set the buffer heads*/
		initFileBuffers();

		/*read the files into the buffers*/
		for(int i=0;i<ftsize;i++)
			fbtable[i].fbsize = readFromFile(fbtable[i].fbhandle,fbtable[i].fbhead,fbufsize);;

		/*start merging and continue till all files have been exhausted*/
		int fcount = ftsize;
		while(fcount){

			int status = mergeBuffers();
			if(status == INBUF_EMPTY){
				
				/*input buffer is empty, fill it and reset fbhead position.*/
				fbtable[MINBUF].fbhead -= fbufsize;
				fbtable[MINBUF].fbsize = readFromFile(fbtable[MINBUF].fbhandle,fbtable[MINBUF].fbhead,fbufsize);
				
				/*check if file is exhausted even after read. if so decrease the file count*/
				if(fbtable[MINBUF].fbsize==0) 
					fcount--;
			
			}if(status == OUTBUF_FULL){
				
				/*output buffer is full, flush it and reset fbhead.*/
				writeToFile(fbtable[OUTBUF].fbhandle,(fbtable[OUTBUF].fbhead)-fbufsize,fbufsize);
				fbtable[OUTBUF].fbhead -= fbufsize;
				fbtable[OUTBUF].fbsize = fbufsize;
			}
		}

	/*flush the remaining output buffer*/
		fbtable[OUTBUF].fbhead -=  (fbufsize-fbtable[OUTBUF].fbsize) ;
		writeToFile(fbtable[OUTBUF].fbhandle,fbtable[OUTBUF].fbhead,fbufsize-fbtable[OUTBUF].fbsize);
	
	}catch(std::exception e){;
	}
	
}

class intComp{

		public: bool operator()(int x, int y){
			return x<y;
		}

}compFunc;

int main(){

	char* ifile = "inputfile.txt";
	char* ofile = "output.txt";


	ExternalSort<int,intComp> es(ifile,ofile,false,compFunc);
	es.sort();

	return 0;

}


