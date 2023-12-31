/*
 * This source file is part of the ace-radius library.  This code was
 * written by Alex Agranov in 2004-2009, and is covered by the BSD open source
 * license. Refer to the accompanying documentation for details on usage and
 * license.
 */

#include <stdio.h>
#include <string.h>

#include "ace-radius/RadiusClientStack.h"

/*
 * A sample RADIUS client. 
 *  
 * Usage: 
 *     client [server-ip]
 *  
 * Notes: 
 *    - if server-ip is not specified, "localhost" is user instead
 *    - client sends Access-Request packet to authentication port (1812)
 *      with user="nemo" and password="arctangent"
 *    - response packet is dumped (if received)
 */

int main (int argc, char *argv[])
{
    printf("Test RADIUS Client application\n");
    
#ifdef _MSC_VER
    WSADATA l_wsaData;
    if(WSAStartup(MAKEWORD(2,0),&l_wsaData) != 0)
    {
        printf("Can not initialize WinSock 2.0\n");
        return 1;
    }
#endif

	// create instance of client stack
    RadiusClientStack l_stack;
    if (!l_stack.isValid())
    {
        printf("Can not create RADIUS client stack\n");
#ifdef _MSC_VER
        WSACleanup();
#endif
        return 1;
    }

    // add connection with some RADIUS server
    if (argc >= 2)
        l_stack.addServer(argv[1], D_RADIUS_AUTHENTICATION_PORT, RadiusSecret("xyzzy5461"));
    else
        l_stack.addServer("localhost", D_RADIUS_AUTHENTICATION_PORT, RadiusSecret("xyzzy5461"));
    
    // create a new packet
    RadiusPacket l_packet(D_PACKET_ACCESS_REQUEST, l_stack);
    
    // add some attributes to the packet
    RadiusAttribute l_attr;
    
    l_packet.addAttribute(D_ATTR_USER_NAME, l_attr);
    l_attr.setString("nemo");

    l_packet.addAttribute(D_ATTR_USER_PASSWORD, l_attr);
    l_attr.setUserPassword("arctangent");

    struct in_addr l_addr;
#ifdef _MSC_VER
    l_addr.S_un.S_addr = inet_addr("192.168.1.16");
#else
    inet_aton("192.168.1.16", &l_addr);
#endif
    l_packet.addAttribute(D_ATTR_NAS_IP_ADDRESS, l_attr);
    l_attr.setIPAddress(l_addr);

    l_packet.addAttribute(D_ATTR_NAS_PORT, l_attr);
    l_attr.setNumber(3);

    l_packet.dump();

    // send the packet
    RadiusPacket * l_response = l_stack.sendPacket(l_packet);

    // print response if it was received
    if (l_response)
    {
        printf("---\nPacket was successfully transmitted\n---\n"); 
        printf("\nResponse packet:\n");
        l_response->dump();
    }
    else
        printf("---\nPacket transmit failure\n---\n"); 

#ifdef _MSC_VER
        WSACleanup();
#endif
    return 0;
}
