#ifndef _DATA_FORMAT_INCLUDE_H_
#define _DATA_FORMAT_INCLUDE_H_

#include<stdint.h>

#include"common.h"

namespace parser{
    namespace szNET{
    using CompID = char[20];
    using Price = uint64_t;
    using Qty = int64_t;
    using Amt = int64_t;
    using SeqNum = int64_t;
    using Boolean = uint16_t;
    using Length = uint32_t;
    using LocalTimeStamp = int64_t;
    using NumInGroup = uint32_t;
    using LocalMktDate = uint32_t;
    using SecurityID = char[8];
    
    using BodyLength = uint32_t;
    using MsgType = uint32_t;
    using Checksum = uint32_t;
    using SenderCompID = CompID;
    using TargetCompID = CompID;
    using Password = char[16];
    using Text = char[200];
    using HeartBInt = int32_t;
    using DefaultApplVerID = char[32];
    using SessionStatus = int32_t;

    using AmountStatus = char;
    using ApplBegSeqNum = SeqNum;
    using ApplEndSeqNum = SeqNum;
    using ApplLastSeqNum = SeqNum;
    using ApplSeqNum = SeqNum;
    using AuctionVolumeTrade = Qty;
    using AuctionValueTrade = Amt;
    using BidApplSeqNum = SeqNum;
    using BusinessRejectReason = uint16_t;
    using BusinessRejectRefID = char[10];
    using BusinessRejectText = char[50];
    using ChannelNo = uint16_t;
    using ComplexEventStartTime = LocalTimeStamp;
    using ComplexEventEndTime = LocalTimeStamp;
    using ConfirmID = char[8];
    using ContactInfo = char[30];
    using Contactor = char[12];
    using EndOfChannel = Boolean;
    using ExecType = char;
    using ExpirationDays = uint16_t;
    using ExpirationType = uint8_t;
    // using FinancialStatus = C8
    using Headline = char[128];
    using InvestorType = char[2];
    using InvestorID = char[10];
    using InvestorName = char[120];
    using LastPx = Price;
    using LastQty = Qty;
    using MarketID = char[8];
    using MarketSegmentID = char[8];
    using MDEntryPx = int64_t;
    using MDEntrySize = Qty;
    using MDEntryType = char[2];
    using MDPriceLevel = uint16_t;
    using MDStreamID = char[3];
    using MemberID = char[6];
    using Memo = char[160];
    using NewsID = char[8];
    using NoComplexEventTimes = NumInGroup;
    using NoMDEntries = NumInGroup;
    using NoMDStreamID = NumInGroup;
    using NoOrders = NumInGroup;
    using NoSubTradingPhaseCode = NumInGroup;
    using NoSwitch = NumInGroup;
    using NumberOfOrders = int64_t;
    using NumTrades = int64_t;
    using OfferApplSeqNum = SeqNum;
    using OrderQty = Qty;
    using OrdType = char;
    using OrigTime = LocalTimeStamp;
    using PosAmt = Amt;
    using PrevClosePx = Price;
    using QuoteID = char[10];
    using RawData = char*;
    using RawDataFormat = char[8];
    using RawDataLength = Length;
    using RefMsgType = uint32_t;
    using RefSeqNum = SeqNum;
    using RejectText = char[16];
    using ResendStatus = uint8_t;
    using ResendType = uint8_t;
    using SecurityIDSource = char[4];
    using SecuritySwitchStatus = Boolean;
    using SecuritySwitchType = uint16_t;
    using SettlPeriod = uint8_t;
    using SettlType = uint16_t;
    using Side = char;
    using StockNum = uint32_t;
    using SubTradingPhaseCode = char[8];
    using TemplateID = uint16_t;
    using ThresholdAmount = Amt;
    using TotalValueTrade = Amt;
    using TotalVolumeTrade = Qty;
    using TraderCode = char[8];
    using TradingPhaseCode = char[8];
    using TradingSessionID = char[4];
    using TradingSessionSubID = char[4];
    using TradingType =  uint8_t;
    using TradSesEndTime = LocalTimeStamp;
    using TradSesStartTime = LocalTimeStamp;
    using TradSesStatus = uint16_t;
    using TransactTime = LocalTimeStamp;
    using UserNum = uint16_t;
    using VersionCode = char[16];

    enum MessageType{
        LogonType=1,
        LogoutType=2,
        HeartbeatType=3,
        ChannelHearbeatType=390095,
        ResendMessageType=390094,
        UserMessageType=390093,
        SnapshotType=390090,
        BusinessRejectType=8,
        RealtimeType=390019,
        RealTimeStockType=390013,
        AnnoucementType=390012,
        // SnapshotType=
        //Order by Deal
        OrderByDealGoodsConcentratedBiddingType=300192,
        OrderByDealAgreementTransactionType=300592,
        OrderByDealRefinancingSecuritiesType=300792,
        OrderByDeaBondMatchType=300292,
        OrderByDealBondSpotTrading=300392,
        //Deal by Deal
        DealByDealGoodsConcentratedBiddingType=300191,
        DealByDealAgreementTransactionType=300591,
        DealByDealRefinancingSecuritiesType=300791,
        DealByDeaBondMatchType=300291,
        DealByDealBondSpotTrading=300391
    };

    static constexpr const int headLength = 8;
    static constexpr const int tailLength = 4;
    struct StandardHead{
        uint32_t MsgType;
        uint32_t bodyLength;
    } packed;

    struct Logon{
        StandardHead standardHead;
        SenderCompID senderCompID;
        TargetCompID targetCompID;
        HeartBInt heartBint;
        Password password;
        DefaultApplVerID defaultApplVerID;
        Checksum checkSum;
    } packed;

    struct Logout{
        StandardHead standardHead;
        SessionStatus sessionStatus;
        Text text;
        Checksum checksum;
    } packed;

    struct Heartbeat{
        StandardHead standardHead;
        Checksum checksum;
    } packed;

    struct ChannelHeartBeat{
        StandardHead standardHead;
        ChannelNo channelNo;
        ApplLastSeqNum applLastSeqNum;
        EndOfChannel endOfChannel;
        Checksum checksum;
    } packed;

    struct ResendMessage{
        StandardHead standardHead;
        ResendType resendType;
        ChannelNo channelNo;
        ApplBegSeqNum applBegSeqNum;
        ApplEndSeqNum applEndSeqNum;
        NewsID newsID;
        ResendStatus resendStatus;
        RejectText rejectText;
        Checksum checksum;
    } packed;

    struct UserMessage{
        StandardHead standardHead;
        OrigTime origTime;
        VersionCode versionCode;
        UserNum userNum;
    } packed;

    struct MDStream {
        MDStreamID mdStreamID;
        StockNum stockNum;
        TradingPhaseCode tradingPhaseCode;
    } packed;

    // struct Snapshot{
    //     StandardHead standardHead;
    //     OrigTime origTime;
    //     ChannelNo channlNo;
    //     NoMDStreamID noMDStreamID,
    //     MDStream* mdStream;
    // } packed;

    struct BusinessReject{
        StandardHead standardHead;
        RefSeqNum refSeqNum;
        RefMsgType refMsgType;
        BusinessRejectRefID businessRejectRefID;
        BusinessRejectReason businessRejectReason;
        BusinessRejectText businessRejectTest;
        Checksum checksum;
    } packed;

    struct Realtime{
        StandardHead standardHead;
        OrigTime origTime;
        ChannelNo channelNO;
        MarketID marketID;
        MarketSegmentID marketSegmentID;
        TradingSessionID tradingSessionID;
        TradingSessionSubID tradingSessionSubID;
        TradSesStatus tradSesStatus;
        TradSesStartTime tradSesStartTime;
        TradSesEndTime tradSesEndTime;
        ThresholdAmount thresholdAmount;
        PosAmt posAmt;
        AmountStatus amoun;
        Checksum checksum;
    } packed;

    struct Switch
    {
        /* data */
        SecuritySwitchType securitySwitchType;
        SecuritySwitchStatus securitySwitchStatus;
    } packed;
    
    struct RealTimeStock{
        StandardHead standardHead;
        OrigTime origTime;
        ChannelNo channelNo;
        SecurityID securityID;
        SecurityIDSource securityIDSource;
        // FinancialStatus financialStatus;
        NoSwitch noSwitch;
        Switch* switch_;
    } packed;

    struct Annoucement{
        StandardHead standardHead;
        OrigTime origTime;
        ChannelNo channelNo;
        NewsID newsID;
        Headline headline;
        RawDataFormat rawDataFormat;
        RawDataLength rawDataLength;
        RawData rawData;
        Checksum checksum;
    } packed;

    struct SnapShotExtendField{

    } packed;

    struct SnapShot{
        StandardHead standardHead;
        OrigTime origTime;
        ChannelNo channelNo;
        MDStreamID mdstream;
        SecurityID securityID;
        SecurityIDSource securitySource;
        TradingPhaseCode tradingPhaseCode;
        PrevClosePx prevClosePx;
        NumTrades numTrades;
        TotalVolumeTrade totalVolumeTrade;
        TotalValueTrade tottalValueTrade;
        SnapShotExtendField extendField;
        Checksum checksum;
    } packed;

    enum OrderExtendFieldType{
        OrderGoodsConcentratedBiddingType=300192,
        OrderAgreementTransactionType=300592,
        OrderRefinancingSecuritiesType=300792,
        OrderBondMatchType=300292,
        OrderBondSpotTrading=300392,
    };

    template<OrderExtendFieldType type>
    struct OrderByDealExtendFields{

    } packed;

    template<>
    struct OrderByDealExtendFields<OrderGoodsConcentratedBiddingType>{
        OrdType orderType;
    } packed;

    template<>
    struct OrderByDealExtendFields<OrderAgreementTransactionType>{
        ConfirmID confirmID;
        Contactor contactor;
        ContactInfo contactInfo;
    } packed;

    template<>
    struct OrderByDealExtendFields<OrderRefinancingSecuritiesType>{
        ExpirationDays expirationDays;
        ExpirationType expirationType;
    } packed;

    template<>
    struct OrderByDealExtendFields<OrderBondMatchType>{
        OrdType orderType;
    } packed;

    template<>
    struct OrderByDealExtendFields<OrderBondSpotTrading>{
        QuoteID quoteID;
        MemberID memberID;
        InvestorType investorType;
        InvestorID investorID;
        InvestorName investorName;
        TraderCode tradeCode;
        SettlPeriod settlePeriod;
        SettlType settleType;
        Memo memo;
    } packed;

    struct OrderByDealHead{
        StandardHead standardHead;
        ChannelNo channelNo;
        ApplSeqNum applSeqNum;
        MDStreamID mdStreamID;
        SecurityID securityID;
        SecurityIDSource securityIDSource;
        Price price;
        OrderQty orderQty;
        Side side;
        TransactTime transTime;
    } packed;

    template<OrderExtendFieldType type>
    struct OrderByDeal{
        OrderByDealHead head;
        OrderByDealExtendFields<type> extendFiels;
        Checksum checksum;
    } packed;

    enum DealExtendFieldsType {
        DealGoodsConcentratedBiddingType=300191,
        DealAgreementTransactionType=300591,
        DealRefinancingSecuritiesType=300791,
        DeaBondMatchType=300291,
        DealBondSpotTrading=300391
    };

    struct DealByDealHead{
        StandardHead standardHead;
        ChannelNo channelNo;
        ApplSeqNum applSeqNum;
        MDStreamID mdStreamID;
        BidApplSeqNum bidApplSeqNum;
        OfferApplSeqNum offerApplSeqNum;
        SecurityID securityID;
        SecurityIDSource securityIDSource;
        LastPx lastPX;
        LastQty lastQty;
        ExecType execType;
        TransactTime transactime;
    } packed;

    template<DealExtendFieldsType type>
    struct DealByDealExtendFields{

    } packed;

    template<>
    struct DealByDealExtendFields<DealGoodsConcentratedBiddingType>{

    } packed;

    template<>
    struct DealByDealExtendFields<DealAgreementTransactionType>{

    } packed;

    template<>
    struct DealByDealExtendFields<DealRefinancingSecuritiesType>{

    } packed;

    template<>
    struct DealByDealExtendFields<DeaBondMatchType>{

    } packed;

    template<>
    struct DealByDealExtendFields<DealBondSpotTrading>{
        SettlPeriod settlePeriod;
        SettlType settleType;
    } packed;

    template<DealExtendFieldsType type>
    struct DealByDeal{
        DealByDealHead head;
        DealByDealExtendFields<type> extendFields;
        Checksum checksum;
    } packed;
    }
}

#endif /** _DATA_FORMAT_INCLUDE_H_ */