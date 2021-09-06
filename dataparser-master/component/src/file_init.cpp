#include"file_init.h"

#include<sys/types.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdint.h>
#include<stdlib.h>

namespace parser{
    char* szDataFileInit::init(const char* __restrict__ fileName){
        this->fd_ = open(fileName, O_RDONLY);
        struct stat statbuf;
        fstat(this->fd_, &statbuf);
        this->filesize_ = static_cast<uint64_t>(statbuf.st_size);
        char* filemem = static_cast<char*>(malloc(this->filesize_));
        uint64_t readLength;
        uint64_t remained = this->filesize_;
        uint64_t readIndex = 0;
        readLength = read(this->fd_, filemem, this->filesize_);
        readIndex += readLength;
        remained -= readLength;
        while(remained > 0){
            readLength = read(this->fd_, filemem+readIndex, remained);
            remained -= readLength;
            readIndex += readLength;
        }

        return filemem;
    }
}