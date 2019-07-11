#if !defined(__USB_PRINTER__)
#define __USB_PRINTER__

/*
 * Unidirectional + GET_PORT_STATUS
 * Bidirectional
 */

#include "Usb.h"

#define USBPRINTER_GET	(USB_SETUP_DEVICE_TO_HOST|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_INTERFACE)
#define USBPRINTER_PUT	(USB_SETUP_HOST_TO_DEVICE|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_INTERFACE)
#define USBPRINTER_REQUEST_DEVICE_ID	(0)
#define USBPRINTER_REQUEST_STATUS		(1)
#define USBPRINTER_REQUEST_SOFT_RESET	(2)

#define USBPRINTER_SUBCLASS_INTERFACE		(1)

#define USBPRINTER_PROTOCOL_UNIDIRECTIONAL	(1)
#define USBPRINTER_PROTOCOL_BIDIRECTIONAL	(2)
#define USBPRINTER_PROTOCOL_IEE1284_4		(3)

class USBPrinter;

class USBPrinterAsyncOper {
    public:

        virtual uint8_t OnInit(USBPrinter *pPrinter __attribute__((unused))) {
            return 0;
        };
};

#define USBPRINTER_MAX_ENDPOINTS               3

class USBPrinter : public USBDeviceConfig, public UsbConfigXtracter, public Stream {
    protected:
        USBHost *pUsb;
        USBPrinterAsyncOper *pAsync;
        uint8_t bAddress;
        uint8_t bConfNum; // configuration number
        uint8_t bIface; // interface value
        uint8_t bNumEP; // total number of EP in the configuration
        uint32_t qNextPollTime; // next poll time
        volatile bool ready; //device ready indicator
        volatile bool bidirectional; //bidirectional protocol
        uint8_t readBuffer[64];
        uint8_t readRemaining;
        uint8_t *readPointer;

        void PrintEndpointDescriptor(const USB_ENDPOINT_DESCRIPTOR* ep_ptr);

    public:
        virtual int available();
        virtual int read();
        virtual int peek();
        virtual void flush() { return; };
        virtual size_t readBytes(char *buffer, size_t length);
        virtual size_t write(const uint8_t *buffer, size_t size);
        virtual size_t write(uint8_t byte) {return write(&byte, 1);};
        virtual size_t write(const char *c_str) {return write(c_str, strlen(c_str));};
        using Print::write;

        static const uint8_t epDataInIndex; // DataIn endpoint index
        static const uint8_t epDataOutIndex; // DataOUT endpoint index
        EpInfo epInfo[USBPRINTER_MAX_ENDPOINTS];

        USBPrinter(USBHost *pusb, USBPrinterAsyncOper *pasync);

        // Methods for receiving and sending data
        uint32_t RcvData(uint16_t *nbytesptr, uint8_t *dataptr);
        uint32_t SndData(uint16_t nbytes, uint8_t *dataptr);
        uint8_t GetStatus();
        uint32_t SoftReset();

        // USBDeviceConfig implementation
        uint32_t Init(uint32_t parent, uint32_t port, uint32_t lowspeed);
        uint32_t Release();
        uint32_t Poll();

        virtual uint32_t GetAddress() {
            return bAddress;
        };

        virtual bool isReady() {
            return ready;
        };

        virtual bool isBidirectional() {
            return bidirectional;
        };

        // UsbConfigXtracter implementation
        void EndpointXtract(uint32_t conf, uint32_t iface, uint32_t alt, uint32_t proto, const USB_ENDPOINT_DESCRIPTOR *ep);
};

#endif // __USB_PRINTER__
