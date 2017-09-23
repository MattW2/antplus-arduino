#ifndef ANTPLUS_BASEPROFILE_h
#define ANTPLUS_BASEPROFILE_h

#include <MainClasses/ANTPLUS_AntPlusRouter.h>
#include "ANT.h"

// Handle circular dependency
class AntPlusRouter;

class BaseProfile {
public:
    BaseProfile();
    BaseProfile(uint8_t deviceNumber);
    /**
     * Returns the last Channel status byte recieved
     */
    uint8_t getChannelStatus();
    /**
     * Called on every message incoming
     */
    void onDataPage(); // TODO fill in params
    /**
     * Called if datapage recieved is not defined in the profile
     */
    void onUnknownDataPage(); // TODO fill in params
    /**
     * Called if datapage has no callback defined or
     * is a manufacturer defined page
     */
    void onOtherDataPage(); // TODO fill in params
    /**
     * Set the channel Id, wildcard is 0
     */
    void setDeviceNumber(uint16_t deviceNumber);
    /**
     * Opens radio channel for RX/TX
     */
    virtual void begin() = 0;
    /**
     * Close radio channel and stop transmitting
     */
    virtual void stop() = 0;

    /******************************************
     *LIBRARY INTERNAL ONLY FUNCTIONS BELOW
     ******************************************/
    virtual void onAcknowledgedData(AcknowledgedData& msg) {}
    virtual void onAdvancedBurstData(AdvancedBurstData& msg) {}
    virtual void onBroadcastData(BroadcastData& msg) {}
    virtual void onBurstTransferData(BurstTransferData& msg) {}
    void setRouter(AntPlusRouter router);
    void setChannelNumber(uint8_t channel);
    void setChannelStatus(uint8_t status);
    void setTransmissionType(uint8_t transmissionType);
    void setSearchTimeout(uint8_t seconds);
protected:
    void setChannelType(uint8_t channelType);
    void setChannelPeriod(uint16_t channelPeriod);
    void setDeviceType(uint8_t deviceType);
    void pushChannelConfig();
    void openChannel();
    void closeChannel();
private:
    AntPlusRouter* _router;
    uint8_t _channel;
    uint8_t _channelType = 0;
    uint16_t _channelPeriod = 0;
    uint16_t _deviceNumber = 0;
    uint8_t _deviceType = 0;
    uint8_t _transmissionType = 0;
};

#endif // ANTPLUS_BASEPROFILE_h