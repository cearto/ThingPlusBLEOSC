// OSCHandler.h
#ifndef OSCHANDLER_H
#define OSCHANDLER_H

#include <OSCMessage.h>

/**
 * @brief Sends an OSC message with no arguments.
 *
 * Usage:
 * ```cpp
 * sendSimpleOSC("/thing/ping");
 * ```
 */
void sendSimpleOSC(const char* address);

/**
 * @brief Sends an OSC message with a single integer argument.
 *
 * Usage:
 * ```cpp
 * sendSampleOSC("/thing/value", 42);
 * ```
 */
void sendSampleOSC(const char* address, int value);

/**
 * @brief Sends an OSC message with multiple integer arguments.
 *
 * Usage:
 * ```cpp
 * int args[3] = {1, 2, 3};
 * sendOSC("/thing/batch", args, 3);
 * ```
 */
void sendOSC(const char *address, const int *args, int numArgs);

/**
 * @brief Route OSC messages to appropriate handler. Must be defined by the main sketch.
 * 
 * Usage:
 * In your main sketch (e.g., ioPin.ino), define a function with this signature:
 * 
 * void routeOSC(OSCMessage &msg) {
 *     if (msg.match("/my/address")) {
 *         // handle message
 *     }
 * }
 */
extern void routeOSC(OSCMessage &msg);

/**
 * @brief Extracts a string argument from an OSCMessage using its internal buffer.
 * 
 * Usage:
 * String val = getStringArg(msg, 1); // Extracts the 1st argument from the OSC message
 * 
 * @param msg Reference to OSCMessage.
 * @param index Index of the string argument (default is 0).
 * @return Extracted String.
 */
String getStringArg(OSCMessage &msg, int index = 0);

/**
 * @brief Extracts an integer argument from an OSCMessage.
 * 
 * Usage:
 * int val = getIntArg(msg, 1); // Extracts the 1st argument as an int
 * 
 * @param msg Reference to OSCMessage.
 * @param index Index of the integer argument (default is 0).
 * @return Extracted integer value.
 */
int getIntArg(OSCMessage &msg, int index = 0);

/**
 * @brief Extracts a float argument from an OSCMessage.
 * 
 * Usage:
 * float val = getFloatArg(msg, 1); // Extracts the 1st argument as a float
 * 
 * @param msg Reference to OSCMessage.
 * @param index Index of the float argument (default is 0).
 * @return Extracted float value.
 */
float getFloatArg(OSCMessage &msg, int index = 0);


#endif // OSCHANDLER_H