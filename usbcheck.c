///////////////////////////////////////////////////////////////////////

#include"usbcheck.h"

///////////////////////////////////////////////////////////////////////
///////////////// check existence of usb flash memory /////////////////

int usbExist(void){
libusb_device  **devList=NULL;
libusb_device *devPtr=NULL;
libusb_device_handle *devHandle=NULL;

struct libusb_device_descriptor devDesc;
unsigned char strDesc[256];
unsigned char devnam[25]="USB DISK";
ssize_t  numUsbDevs=0;
ssize_t count=0;
int retval=0;
int ret=0;
retval =libusb_init(NULL);
numUsbDevs=libusb_get_device_list(NULL,&devList);
while(count< numUsbDevs){

  devPtr=devList[count];
  retval=libusb_open(devPtr,&devHandle);
//printf("1%d\n",count);
  if(retval=LIBUSB_SUCCESS) {
//    printf("2\n");
    retval=libusb_get_device_descriptor(devPtr,&devDesc);
    if(retval=LIBUSB_SUCCESS){
//      printf("3\n");
      if(devDesc.iProduct>0){
//        printf("4\n");
        retval=libusb_get_string_descriptor_ascii(devHandle,devDesc.iProduct,strDesc,256);
        if(retval>=0) {
//          printf("5\n");
          if (strstr(strDesc,devnam)!=NULL)
            ret=1;
        }
      }
    }
    //printf("exists\n");
  }//end if
  libusb_close(devHandle);
  devHandle=NULL;
  count++;
}//end while
libusb_exit(NULL);
return ret;
}//end usbExist

///////////////////////////////////////////////////////////////////////
