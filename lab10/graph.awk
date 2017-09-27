BEGIN {
	recv = 0
	 }
	 
 {
         # Trace line format: normal
         if ($2 != "-t") {
                 event = $1
                 time = $2
                 if (event == "+" || event == "-") node_id = $3
                 if (event == "r" || event == "d") node_id = $4
                 flow_id = $8
                 pkt_id = $12
                 pkt_size = $6
         }
 
        # Calculate total received packets' size
         if (event == "r") {
                 if (flow_t != "sctp") {
                         recv += pkt_size - hdr_size
                         printf("%g  %g\n",time,(recv/time)*(8/1000))
                 } else {
                        # Rip off SCTP header, whose size depends
                         # on the number of chunks in each packet
                         if (pkt_size == 40) pkt_size = 0
                         if (pkt_size == 448) pkt_size = 400
                         if (pkt_size == 864) pkt_size = 800
                         if (pkt_size == 1280) pkt_size = 1200
                         recv += pkt_size
                         printf("%g  %g\n",time,(recv/time)*(8/1000))
                 }
         }
 }
 
 END {
        #printf("The throughput is  %10g\n",(recv/time)*(8/1000))

 }
 
