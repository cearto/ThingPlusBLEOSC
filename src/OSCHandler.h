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
 */
extern void routeOSC(OSCMessage &msg);

#endif // OSCHANDLER_H