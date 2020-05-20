#include "packetPool.hpp"
#include "sniffer.hpp"
#include "coreFunctions.hpp"
#include <unistd.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#include <linux/netfilter.h>
#include <libnetfilter_queue/libnetfilter_queue.h>


using std::cout;
using std::endl;

int nfq_cb(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg, struct nfq_data *nfd, void *data) {
	struct nfqnl_msg_packet_hdr *ph = nfq_get_msg_packet_hdr(nfd);
	struct nfqnl_msg_packet_hw* hw = nfq_get_packet_hw(nfd);
	unsigned int id = ntohl(ph->packet_id);
	printf("callback: protocol=0x%04x id=%u src=", ntohs(ph->hw_protocol), id);
	if(hw)
	{
		for(int i=0; i<ntohs(hw->hw_addrlen)-1; i++)
			printf("%02x:", hw->hw_addr[i]);
		printf("%02x\n", hw->hw_addr[ntohs(hw->hw_addrlen) - 1]);
	}
	else
		printf("none\n");
	
	return nfq_set_verdict(qh, id, NF_ACCEPT, 0, NULL);
}

int main1()
{
	pinat::Sniffer* s = new pinat::Sniffer("br0", "", "ap0", "enp1s0", "08:6a:0a:22:12:1a");
	unsigned long p = 0;
	while(true)
	{
		p = s->getPacket();
		s->forwardPacket(p);
	}

	delete s;

	return 0;
}

int main2()
{
	struct nfq_handle* h;
	struct nfq_q_handle* qh;
	int fd;
	int rv;
	uint32_t queue = 0;
	char buf[4096] __attribute__ ((aligned));

	h = nfq_open();
	if(!h) {
		printf("error nfq_open\n");
		return 1;
	}

	qh = nfq_create_queue(h, queue, &nfq_cb, NULL);
	if(!qh) {
		printf("error create_queue\n");
		nfq_close(h);
		return 1;
	}

	if(nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff) < 0) {
		printf("error set_mode\n");
		nfq_close(h);
		nfq_destroy_queue(qh);
		return 1;
	}

	fd = nfq_fd(h);
	while (true) {
		if((rv = recv(fd, buf, sizeof(buf), 0)) >= 0) {
			nfq_handle_packet(h, buf, rv);
		}
		else
		{
			printf("error recv\n");
			break;
		}
		
	}

	nfq_destroy_queue(qh);
	nfq_close(h);

	return 0;
}

int main(int argc, char** argv)
{
	if(getuid() != 0)
	{
		cout << "call as root" << endl;
		return 1;
	}
	
	return main2();
}