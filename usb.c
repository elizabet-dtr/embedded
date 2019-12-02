#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <limits.h>

const static int ENDPOINT_INT_IN=0x81; /* endpoint 0x81 address for IN */
const static int ENDPOINT_INT_OUT=0x02; /* endpoint 1 address for OUT */

int main(int argc, unsigned char *argv[])
{
	libusb_device_handle *h;	
	libusb_context *c = NULL;
	unsigned char dataLeds[] = { 1, 3, 0xA}; //Rotating
	int error, transferred;

	/*------------ Initilizing libusb  ------------*/	
	error = libusb_init(NULL);
	
	/*------------ Set debug mode level 4  ------------*/
	libusb_set_debug(c,2); 
	
	/*------------ Open USB device with vid & pid  ------------*/
	h = libusb_open_device_with_vid_pid(NULL, 0x045e, 0x028e);
	
	/*------------ Check if device is open  ------------*/	
	if (h == NULL) {
		fprintf(stderr, "Failed to open device\n");
		return (1);
	}
	
	/*------------ Kernel and Interface  ------------*/
     
    if (libusb_kernel_driver_active(h, 0) == 1)
    {
        if ((error = libusb_detach_kernel_driver(h, 0)) != 0)
        {
            fprintf(stderr, "ERROR: libusb_detach_kernel_driver() failed: %d\n", error);
           
        }
    }
    if ((error = libusb_claim_interface(h, 0)) != 0)
    {
		fprintf (stderr, "ERROR: libusb_claim_interface() failed: %d\n", error);                     
    }
    
    /*------------ Rotating light(write to USB) ------------*/
	if ((error = libusb_interrupt_transfer(h, ENDPOINT_INT_OUT, dataLeds, sizeof dataLeds, &transferred, 0)) != 0) {
		fprintf(stderr, "Transfer failed: %d\n", error);
		return (1);
	}
	
	/*------------ Rumbling motor ------------*/
	int z=0;
	while(z<500)
	{	 
		z++;
		uint8_t vibrateData[8] = {0x00,0x08,0x00, 0xAA, 0xAA, 0x00, 0x00, 0x00};
		error = libusb_interrupt_transfer(h, ENDPOINT_INT_OUT, vibrateData, sizeof vibrateData, &transferred,0);
	 	 
		if(z==500)
		{
			uint8_t vibrateData[8] = {0x00,0x08,0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
			error = libusb_interrupt_transfer(h, ENDPOINT_INT_OUT, vibrateData, sizeof vibrateData, &transferred,0);
		}
	}

	/*------------ Reading Button Status ------------*/
	uint8_t	readData[20];
	while(1)
	{
		error = libusb_interrupt_transfer(h, ENDPOINT_INT_IN, readData, sizeof readData, &transferred,0);
		int j;
		for( j=0; j<sizeof readData; j++)
		{
			printf("%2x ", readData[j]);
		}
		printf("\n");
	}
	
    if (error < 0) 
    {
		fprintf(stderr, "Interrupt read error %d\n", error);		
    }
    
    if(error == 0)
    {
		 printf("Reading complete\n");
	}
	
	/*------------ Uninitializing USB ------------*/
	libusb_release_interface(h, 0);
    libusb_close(h); 
    libusb_exit(NULL); 

	return (0);
}
