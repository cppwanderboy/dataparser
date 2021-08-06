#ifndef _FILE_INIT_INCLUDE_H_
#define _FILE_INIT_INCLUDE_H_

#include"common.h"

#include<stdint.h>
#include<unistd.h>

namespace parser{
    class szDataFileInit{
    public:
        szDataFileInit():fd_(-1), filesize_(0){};
        ~szDataFileInit(){
            this->destruct();
        }
        szDataFileInit(const szDataFileInit&)=default;
        szDataFileInit& operator=(const szDataFileInit&)=default;
        
        char* init(const char* __restrict__ fileName);

        uint64_t get_size()const {return this->filesize_;}

    private:
        void destruct()noexcept{
            if(unlikely(this->fd_ == -1)){
                return;
            }
            close(this->fd_);
        }
    private:
        int fd_;
        uint64_t filesize_;
    };

}

#endif /** _FILE_INIT_INCLUDE_H_ */