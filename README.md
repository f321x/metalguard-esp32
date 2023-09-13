# metalguard-esp32
The touch pins of an esp32 microcontroller can be used to send a notification when a connected metal part is being touched with finger.
In combination with the deep sleep feature of an esp32 and a lithium battery this can be used to monitor a piece of metal for years with minimum attention.

This repository is intended to provide all the necessary code and documentation to set up an esp32 to monitor a piece of metal by an enthusiastic beginner (techie).

Time needed: one Sunday evening

# Chapters
1. [Introduction](#introduction)  
2. [Hardware](#paragraph1)    
3. [Preparing the necessary software](#paragraph2)
4. [Create a Telegram Bot](#paragraph3)
5. [Configuring the firmware](#paragraph4)
6. [Flashing the esp32](#paragraph5)    
7. [Beheading the esp32](#paragraph6)
8. [Putting everything together](#paragraph7)
9. [Support](#paragraph8)
10. [Donation](#paragraph9)

## 2. Hardware
- ESP-WROOM-32 microcontroller dev board, i used a "ESP32 NodeMCU" (~7€), recommended to buy on serious plattform to avoid malfunctioning fakes
- male-male jump wires (~2€ on aliexpress)
- CR123A Lithium batterie(s)
- case for CR123 batteries (either Aliexpress or 3D printed)
- fine soldering iron + solder
- silicone or hot glue 

## 3. Preparing the necesary software
To flash the firmware on the ESP32 you will need a computer with the right software.
In this documentation i show the usage of Visual Studio Code with the PlattformIO.

1. Install Visual Studio Code (https://code.visualstudio.com/)
2. Install the PlattformIO Extension (https://platformio.org/install/ide?install=vscode)
3. Watch this 10min PlattformIO introduction (https://www.youtube.com/watch?v=PYSy_PLjytQ)
4. **If** you are running **GNU/Linux** you will probably need to set up udev rules for the esp32 to be able to communicate with the computer (https://docs.platformio.org/en/stable//core/installation/udev-rules.html)
5. Download/Clone this repository
6. In the PlattformIO main screen, click "Open Project", open this project in the repository

## 4. Creating a Telegram bot
In my setup i used Telegram to get quick and reliable notifications on my smartphone. You could also implement E-Mail, Nostr, ham radio or any other kinds of communication.

If you want to follow this guide you will need to set up a Telegram bot to continue.
You will need the API token of the bot and the chat ID of your Telegram account.

**How to create the Telegram bot with Botfather and get the api key:** https://sendpulse.com/knowledge-base/chatbot/telegram/create-telegram-chatbot

**How to get your Chat ID:** https://www.alphr.com/find-chat-id-telegram/
  -> TLDR: search for some "Chat ID" bot in the Telegram app, contact it and you will get your chat ID if you messaged a working bot :D

Now you should have 2 strings like the following examples:

Bot API token: 123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11

Chat ID: 210987654

## 5. Configuring the Firmware:
In the folder **src** open the file **main.cpp** (in VS Code)

Here you can see the following part in line 4-12:

~~~
#define WIFI_SSID "YOUR WIFI NAME"
#define WIFI_PASS "YOUR WIFI PASSWORD"
#define BOT_TOKEN "YOUR TELEGRAM BOT TOKEN"
#define CHAT_ID "YOUR TELEGRAM CHAT ID"
#define Threshold 50  // how sensitive the touch detection should be, higher == more sensitive

unsigned long long sleep_duration = 2592000000000;    // 30 days
// unsigned long long sleep_duration = 3600000008;     // 1 hour
// unsigned long long sleep_duration = 86400000192; // ~24 hours
~~~

Set your **wifi** and **telegram** credentials in the code. 

Set the **touch sensibility** with **Treshold**, higher is more sensitive. 50 is already pretty sensitive.

**sleep_duration** is the time interval in µs in which the esp will send you a test notification as status to notice if the battery is empty. (only one has to be active the others are commented out with //)


## 6. Flashing the esp32
To flash the configured firmware to the esp32:
1. Connect the esp32 to your computer over usb
2. Go to the PlattformIO home screen (little house in the bottom bar)
3. Open the **Devices** register and copy the address of your esp32
4. Open the file plattformio.ini in your project folder and add:
~~~
upload_port = /your/device/path (for example /dev/ttyUSB0)
~~~
5. Now you can click on the arrow in the bottom bar to upload the firmware to the esp32. It will be compiled and uploaded automatically. In case of errors look them up on Google (or Kagi).

The esp is now ready and you should be able to test it.
Connect it to a power supply and touch the **GPIO PIN 15 (T3)**, or connect a cable to it and touch the cable.
You should get a Telegram message in some seconds if everything is configured correctly and the esp32 is in range of the configured wifi network.

## 7. Beheading the esp32
Supplying the esp32 over the dev board would increase the energy usage, also the esp32 is easier to hide if not mounted on a dev board.
Warning: you won't be able to easily flash the esp32 again after **unsoldering** it from the dev board and will only be able to supply it with **3.3V** as it has no voltage converter integrated.

![esp32bild](https://github.com/f321x/metalguard-esp32/assets/51097237/35158725-3b9b-4dfb-923f-7a2a386c9d25)

To desolder the esp32 from its dev board i used a hot air gun from the back of the board and pulled the esp chip from the board after the solder got loose.

## 8. Putting everything together
1. Solder CR123 battery holder to 3.3V pin (VIN) + EN Pin and ground pin (GND) of the esp32.
2. Solder cable to touch pin (GPIO 15, also called TOUCH3)
3. Attach other end of the touch cable to your valuable metal part. If you want to monitor a non conductive part you can also wrap it in aluminum foil and attach the touch cable to the aluminum foil.
4. Insert the CR123 battery in the battery holder.
5. Test your setup if everything is functioning as inteded.
6. Sleep well with your new safety system :D

![ESP32-wroom-32-pinout-mischianti-high-resolution](https://github.com/f321x/metalguard-esp32/assets/51097237/785182e8-483d-45da-a264-765fb481c3a8)

## 9. Support
If you need help assembling this or encountered any problems you can connect with others in this Telegram group chat: https://t.me/+T_DB7qpHodI4ZDNi

## 9. Donation
In case this guide and the code is useful for you or lets you sleep better feel free to send me some satoshis to the following lightning address: x@lnaddress.com
