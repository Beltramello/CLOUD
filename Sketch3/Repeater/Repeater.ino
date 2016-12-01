//****************************************************//
//                                                    //
//                 CLOUD   Repeater                   //     
//                                                    // 
//****************************************************//

/*
Name:		Repeater
Created:	01/12/2016 3:17:16 PM
Author:		Carlos Beltramello
Company:	QL Labor - Continental AG
*/


//Required libraries
#include "variant.h"
#include <due_can.h>



//********************INIT Parameters*****************//
void setup()
{
	Can1.begin(CAN_BPS_500K); // Initialize Can1, Set the proper baud rates here//
	Can0.begin(CAN_BPS_500K); // Initialize Can1, Set the proper baud rates here//

	// Initialize Can1 Mailboxs
	/*Can1.reset_all_mailbox();
	Can1.disable_interrupt(CAN_DISABLE_ALL_INTERRUPT_MASK);*/

	//---------------------------IER_Register------------------------------------------------//
	//   | - | - | - |BERR||FERR|AERR|SERR|CERR||TSTP|TOVF|WAKE|SLEEP||BOFF|ERRP|WARN|ERRA|| //
	//   | 0 | 0 | 0 |  1 ||  1 |  1 |  1 | 1  ||  1 |  1 |  0 |  0  || 1  | 1  | 0  |  1 || //
	//																    			    	 //
	//   |- | - | - | - || - | - | - | - ||MB7|MB6|MB5|MB4||MB3|MB2|MB1|MB0|				 //
	//   |0 | 0 | 0 | 0 || 0 | 0 | 0 | 0 || 0 | 1 | 1 | 1 || 1 | 1 | 0 | 1 |				 //												
	//---------------------------------------------------------------------------------------//
	Can1.enable_interrupt(0x1FCD007D);
	Can0.enable_interrupt(0x1FCD007D);


	//***********************************************//
	//			Mode of Mailboxes					 //
	//***********************************************//
	Can1.mailbox_set_mode(0, CAN_MB_RX_MODE);	//MAILBOX 0 Receive mailbox
	Can1.mailbox_set_mode(1, CAN_MB_TX_MODE);	//MAILBOX 1 Transmit mailbox
	Can1.mailbox_set_mode(2, CAN_MB_RX_MODE);	//MAILBOX 2 Receive mailbox
	Can1.mailbox_set_mode(3, CAN_MB_RX_MODE);	//MAILBOX 3 Receive mailbox
	Can1.mailbox_set_mode(4, CAN_MB_RX_MODE);	//MAILBOX 4 Receive mailbox
	Can1.mailbox_set_mode(5, CAN_MB_RX_MODE);	//MAILBOX 5 Receive mailbox
	Can1.mailbox_set_mode(6, CAN_MB_RX_MODE);	//MAILBOX 6 Receive mailbox
	Can1.mailbox_set_mode(7, CAN_MB_TX_MODE);	//MAILBOX 7 Transmit mailbox

	Can0.mailbox_set_mode(0, CAN_MB_RX_MODE);	//MAILBOX 0 Receive mailbox
	Can0.mailbox_set_mode(1, CAN_MB_TX_MODE);	//MAILBOX 1 Transmit mailbox
	Can0.mailbox_set_mode(2, CAN_MB_RX_MODE);	//MAILBOX 2 Receive mailbox
	Can0.mailbox_set_mode(3, CAN_MB_RX_MODE);	//MAILBOX 3 Receive mailbox
	Can0.mailbox_set_mode(4, CAN_MB_RX_MODE);	//MAILBOX 4 Receive mailbox
	Can0.mailbox_set_mode(5, CAN_MB_RX_MODE);	//MAILBOX 5 Receive mailbox
	Can0.mailbox_set_mode(6, CAN_MB_RX_MODE);	//MAILBOX 6 Receive mailbox
	Can0.mailbox_set_mode(7, CAN_MB_TX_MODE);	//MAILBOX 7 Transmit mailbox


	//***********************************************//
	//			Mask filter of Mailboxes			 //
	//***********************************************//
	Can1.setRXFilter(0,0x000, 0x700, false);
	Can1.setRXFilter(2, 0x100, 0x7F0, false);
	Can1.watchFor();

	Can0.setRXFilter(0, 0x000, 0x700, false);
	Can0.setRXFilter(2, 0x100, 0x7F0, false);
	Can0.watchFor();

	//***********************************************//
	//  now register all of the callback functions   //
	//***********************************************//

	//Callback for CAN0
	Can0.setCallback(0, Repeater_callback00);
	Can0.setCallback(2, Repeater_callback02);
	Can0.setGeneralCallback(Repeater_callback0G);

	//Callback for CAN1
	Can1.setCallback(0, Repeater_callback10);
	Can1.setCallback(2, Repeater_callback12);
	Can1.setGeneralCallback(Repeater_callback1G);

	//to low current consumption
	USBDevice.detach();		  //USB Core disable	
	pmc_disable_periph_clk(ID_ADC); //AD converter Disable

}


void loop()
{

}

