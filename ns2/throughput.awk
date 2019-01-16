#!/usr/bin/sh
BEGIN {
       recSize = 0
       strtTime = 100000
       stpTime = 0
       count=0
  }
  {
  	#trace file headings 
       if ($2 == "-t") {
             ev = $1
             time = $3 
             nodeId = $5
             pktId = $41
             pktSize = $37
             level = $19
       }
  #start time
  if (level == "AGT" && (ev == "+" || ev == "s") && pktSize >= 512) {
     sent++
    if (time < strtTime) {
             strtTime = time
             }
    #stores the starting time of pkt transmission in strt[pktId]
    strt[pktID]=strtTime	
 	}
# Update rcvd pkt size and store pkt's arrival time
 if (level == "AGT" && ev == "r" && pktSize >= 512) {
receive++
       if (time > stpTime) {
             stpTime = time
             }
       hdr_size = pktSize % 512
       #Subtract packet header size
       pktSize -= hdr_size
       #store current packet size
       recSize += pktSize
       }
       #stores the stopping time of pkt transmission in stp[pktId]
	stp[pktId]=stpTime;
 	count=pktId; 
 }
  END {
       for(i=0;i<=count;i++){printf("%8d : %.2f \n",i,stp[i]-strt[i]);}     
       printf("PacketID : dropdelay\n");
	printf("sent_packets\t %d\n",sent);
  printf("received_packets %d\n",receive);
  printf("PDR %.2f\n",((receive/sent)*100));
       printf("Avg Throughput[kbps] =%.2f\nstrtTime=%.2f\nstpTime=%.2f\n",(recSize/(stpTime-strtTime))*(8/1000),strtTime,stpTime)      
}