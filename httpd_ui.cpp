		#include <ESPUI.h>
		// true for verbose, false for quiet
		ESPUIClass ESPUI( Verbosity::VerboseJSON );


// *********** External Variables 
	#include "wifi-ota.h"					// get the wifi structures
	extern wifi_Struct wifi_cfg;			// link to wifi variable wifi_cfg



uint16_t button1;




void numberCall( Control* sender, int type ) {
  Serial.println( sender->value );
}

void textCall( Control* sender, int type ) {

    uint8_t selectit = 255;
    if (sender->label == "Name:")
        selectit = 0;
    else if (sender->label == "Password")
        selectit = 1;
        

    switch(selectit)
    {
        case 0:
            Serial.println("nameIT");
            break;

        case 1:
         Serial.println("Password");
            break;
        


    }

  Serial.print("Text: ID: ");
  Serial.print(sender->id);
  Serial.print(", Value: ");
  Serial.println( sender->value );
  Serial.println(sender->label);
  
  }
  

void slider( Control* sender, int type ) {
  Serial.print("Slider: ID: ");
  Serial.print(sender->id);
  Serial.print(", Value: ");
  Serial.println( sender->value );}

void buttonCallback( Control* sender, int type ) {
  switch ( type ) {
    case B_DOWN:
      Serial.println( "Button DOWN" );
      break;

    case B_UP:
      Serial.println( "Button UP" );
      break;
  }
}

void buttonExample( Control* sender, int type ) {
  switch ( type ) {
    case B_DOWN:
      Serial.println( "Status: Start" );
      ESPUI.updateControl( "Status:", "Start" );
    
      ESPUI.getControl( button1 )->color = ControlColor::Carrot;
      ESPUI.updateControl( button1 );
      break;

    case B_UP:
      Serial.println( "Status: Stop" );
      ESPUI.updateControl( "Status:", "Stop" );
   
      ESPUI.getControl( button1 )->color = ControlColor::Peterriver;
      ESPUI.updateControl( button1 );
      break;
  }
}

void padExample( Control* sender, int value ) {
  switch ( value ) {
    case P_LEFT_DOWN:
      Serial.print( "left down" );
      break;

    case P_LEFT_UP:
      Serial.print( "left up" );
      break;

    case P_RIGHT_DOWN:
      Serial.print( "right down" );
      break;

    case P_RIGHT_UP:
      Serial.print( "right up" );
      break;

    case P_FOR_DOWN:
      Serial.print( "for down" );
      break;

    case P_FOR_UP:
      Serial.print( "for up" );
      break;

    case P_BACK_DOWN:
      Serial.print( "back down" );
      break;

    case P_BACK_UP:
      Serial.print( "back up" );
      break;

    case P_CENTER_DOWN:
      Serial.print( "center down" );
      break;

    case P_CENTER_UP:
      Serial.print( "center up" );
      break;
  }

  Serial.print( " " );
  Serial.println( sender->id );
}

void switchExample( Control* sender, int value ) {
  switch ( value ) {
    case S_ACTIVE:
      Serial.print( "Active:" );
      break;

    case S_INACTIVE:
      Serial.print( "Inactive" );
      break;
  }

  Serial.print( " " );
  Serial.println( sender->id );
}

void selectExample( Control* sender, int value ) {
  Serial.print("Select: ID: ");
  Serial.print(sender->id);
  Serial.print(", Value: ");
  Serial.println( sender->value );
}

void otherSwitchExample( Control* sender, int value ) {
  switch ( value ) {
    case S_ACTIVE:
      Serial.print( "Active:" );
      break;

    case S_INACTIVE:
      Serial.print( "Inactive" );
      break;
  }

  Serial.print( " " );
  Serial.println( sender->id );
}




// HTTP Extras



// END HTTP extras





void httpd_setupUI()
{

  uint16_t tab1 = ESPUI.addControl( ControlType::Tab, "Master", "Master" );
  uint16_t tab2 = ESPUI.addControl( ControlType::Tab, "Wifi", "Wifi" );
  uint16_t tab3 = ESPUI.addControl( ControlType::Tab, "Settings 3", "Settings 3" );

  // shown above all tabs
  //ESPUI.addControl( ControlType::Label, "Status:", "Stop", ControlColor::Turquoise );



    // Tab1 Master
  uint16_t select1 = ESPUI.addControl( ControlType::Select, "Load:", "", ControlColor::Alizarin, tab1, &selectExample );
  ESPUI.addControl( ControlType::Option, "Startup", "S0", ControlColor::Alizarin, select1 );
  ESPUI.addControl( ControlType::Option, "S1", "S1", ControlColor::Alizarin, select1 );
  ESPUI.addControl( ControlType::Option, "S2", "S2", ControlColor::Alizarin, select1 );
  


    // Tab2 Wifi

  ESPUI.addControl( ControlType::Text, "Name:", wifi_cfg.APname, ControlColor::Alizarin, tab1, &textCall );
  ESPUI.addControl( ControlType::Text, "Password:", wifi_cfg.pwd, ControlColor::Alizarin, tab1, &textCall );

  // tabbed controls
  ESPUI.addControl( ControlType::Label, "Millis:", "0", ControlColor::Emerald, tab1 );
  ESPUI.addControl( ControlType::Button, "Push Button", "Press", ControlColor::Peterriver, tab1, &buttonCallback );
  ESPUI.addControl( ControlType::Button, "Other Button", "Press", ControlColor::Wetasphalt, tab1, &buttonExample );



  ESPUI.addControl( ControlType::PadWithCenter, "Pad with center", "", ControlColor::Sunflower, tab2, &padExample );
  ESPUI.addControl( ControlType::Pad, "Pad without center", "", ControlColor::Carrot, tab3, &padExample );
  ESPUI.addControl( ControlType::Switcher, "Switch one", "", ControlColor::Alizarin, tab3, &switchExample );
  ESPUI.addControl( ControlType::Switcher, "Switch two", "", ControlColor::None, tab3, &otherSwitchExample );


  ESPUI.addControl( ControlType::Slider, "Slider one", "30", ControlColor::Alizarin, tab1, &slider );


  ESPUI.addControl( ControlType::Slider, "Slider two", "100", ControlColor::Alizarin, tab3, &slider );
  ESPUI.addControl( ControlType::Number, "Number:", "50", ControlColor::Alizarin, tab3, &numberCall );

		ESPUI.begin("TPM Control");
}

