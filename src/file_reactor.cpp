#include"szData_parser.h"

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include <arpa/inet.h>
#include<iostream>

#include"file_reactor.h"

namespace parser{
    using namespace parser::szNET;

    template<>
    int szDataParser::findFD<OrderByDealGoodsConcentratedBiddingType>(char* codeChar, const char* directory, const int length){
        int codeInt = this->getcodeInt(codeChar);

        if(this->ordercode2file_.find(codeInt) == this->ordercode2file_.end()){
            const int length_ = length + 11;// xxx/xxxxxx.csv length + 6 + 4 + 1
            char fileAddr[length_];
            memcpy(fileAddr, directory, length);
            char* filename_ = fileAddr + length;
            filename_[0] = codeChar[0];
            filename_[1] = codeChar[1];
            filename_[2] = codeChar[2];
            filename_[3] = codeChar[3];
            filename_[4] = codeChar[4];
            filename_[5] = codeChar[5];
            filename_[6] = '.';
            filename_[7] = 'c';
            filename_[8] = 's';
            filename_[9] = 'v';
            filename_[10] = '\0';
            int write_fd = open(fileAddr, O_RDWR|O_CREAT, 0666);
            this->ordercode2file_[codeInt] = write_fd;
            this->write_fdvec_.push_back(write_fd);
        }
        return this->ordercode2file_[codeInt];
    }

    template<>
    int szDataParser::findFD<DealByDealGoodsConcentratedBiddingType>(char* codeChar, const char* directory, const int length){
        int codeInt = this->getcodeInt(codeChar);

        if(this->dealcode2file_.find(codeInt) == this->dealcode2file_.end()){
            const int length_ = length + 11;// xxx/xxxxxx.csv length + 6 + 4 + 1
            char fileAddr[length_];
            memcpy(fileAddr, directory, length);
            char* filename_ = fileAddr + length;
            filename_[0] = codeChar[0];
            filename_[1] = codeChar[1];
            filename_[2] = codeChar[2];
            filename_[3] = codeChar[3];
            filename_[4] = codeChar[4];
            filename_[5] = codeChar[5];
            filename_[6] = '.';
            filename_[7] = 'c';
            filename_[8] = 's';
            filename_[9] = 'v';
            filename_[10] = '\0';
            int write_fd = open(fileAddr, O_RDWR|O_CREAT, 0666);
            this->dealcode2file_[codeInt] = write_fd;
            this->write_fdvec_.push_back(write_fd);
        }
        return this->dealcode2file_[codeInt];
    }

    void szDataParser::main_run(const char* __restrict__ file_name){
        char* file_mem = this->init_.init(file_name);
        char* process_mem = file_mem;
        uint64_t totalLength;
        uint64_t filesize = this->init_.get_size();
        int i = 0;
        while(filesize > 0){
            StandardHead* head = (StandardHead*)process_mem;
            MessageType messtype = (MessageType)ntohl(head->MsgType);
            // std::cout<<"messtype "<<messtype<<std::endl;
            uint32_t bodylength = ntohl(head->bodyLength);
            // std::cout<<"bodyLength "<<bodylength<<std::endl;
            switch(messtype){
            case OrderByDealGoodsConcentratedBiddingType:{
                i = 1;
                using DataGram = OrderByDeal<OrderGoodsConcentratedBiddingType>*;
                DataGram datagram = (DataGram)process_mem;

                int fd = findFD<OrderByDealGoodsConcentratedBiddingType>(datagram->head.securityID, "order/", 6);
                OrderFileReactor reactor{};
                reactor(fd, datagram);
                i = 0;
                break;
            }
            case DealByDealGoodsConcentratedBiddingType:{

                i = 2;
                using DataGram = DealByDeal<DealGoodsConcentratedBiddingType>*;
                DataGram datagram = (DataGram)process_mem;
                
                int fd = findFD<DealByDealGoodsConcentratedBiddingType>(datagram->head.securityID, "deal/", 5);
                DealFileReactor reactor{};
                reactor(fd, datagram);
                i = 0;
                break;
            }
            default:
                break;
            }
            totalLength = headLength + bodylength + tailLength;
            process_mem = process_mem + totalLength;
            filesize -= totalLength;
            // std::cout<<"filesize "<<filesize<<std::endl;
        }
        std::cout<<filesize<<std::endl;
        free(file_mem);
    }
}