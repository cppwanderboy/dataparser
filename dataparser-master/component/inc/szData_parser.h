#ifndef _SZDATAPARSER_INCLUDE_H_
#define _SZDATAPARSER_INCLUDE_H_

#include<stdint.h>

#include<map>
#include<vector>

#include"data_format.h"
#include"file_init.h"

namespace parser{
    using namespace parser::szNET;
    class szDataParser{
    public:
        szDataParser():read_fd_(-1){}
        ~szDataParser(){
            if(unlikely(this->read_fd_ == -1)){
                return;
            }
            close(read_fd_);
            for(auto write_fd: write_fdvec_){
                close(write_fd);
            }
        }

        void main_run(const char* __restrict__ file_name);
    private:
        inline char* init(const char* __restrict__ file_name);
        template<MessageType type>
        int findFD(char* code, const char* directory, const int length){return 0;}
        inline int getcodeInt(const char* __restrict__ code);
    private:
        int read_fd_;
        szDataFileInit init_;

        std::map<int, int> ordercode2file_;
        std::map<int, int> dealcode2file_;

        std::vector<int> write_fdvec_;
    };

    inline char* szDataParser::init(const char* __restrict__ file_name){
        return this->init_.init(file_name);
    }

    inline int szDataParser::getcodeInt(const char* __restrict__ ptr) {
        int nums1 = (ptr[0] - '0');
        int nums2 = (ptr[1] - '0');
        int nums3 = (ptr[2] - '0');
        int nums4 = (ptr[3] - '0');
        int nums5 = (ptr[4] - '0');
        int nums6 = (ptr[5] - '0');
    
        return (nums1 << 16) + (nums1 << 15) + (nums1 << 10) + (nums1 << 9) + (nums1 << 7) + (nums1 << 5) +
            (nums2 << 13) + (nums2 << 10) + (nums2 << 9) + (nums2 << 8) + (nums2 << 4) +
            (nums3 << 9) + (nums3 << 8) + (nums3 << 7) + (nums3 << 6) + (nums3 << 5) + (nums3 << 3) +
            (nums4 << 6) + (nums4 << 5) + (nums4 << 2) +
            (nums5 << 3) + (nums5 << 1) +
            nums6;
    }


    
}

#endif /**_SZDATAPARSER_INCLUDE_H_*/
