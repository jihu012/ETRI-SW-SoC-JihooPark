`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/08/09 12:18:32
// Design Name: 
// Module Name: fsm
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module fsm #(parameter READ_LATENCY=3,parameter ADDR_WIDTH=15,parameter DATA_WIDTH=31)(clk,reset,wea_bram,addra,dina,douta,ena_bram,valid);

input clk,reset;
input wea_bram;
input [ADDR_WIDTH-1:0] addra;
input ena_bram;
input [DATA_WIDTH-1:0] dina;
output [DATA_WIDTH-1:0] douta;
output valid;
 
 localparam IDLE=2'b00,WAIT=2'b01,READ=2'b11;
 reg enable;
 reg [1:0] cstate,nstate;
 reg [2:0] wait_counter;
 reg valid;
 wire [DATA_WIDTH-1:0] dina;
 wire [DATA_WIDTH-1:0] douta;
 wire [ADDR_WIDTH-1:0] addra;
 wire [DATA_WIDTH-1:0] douta_bram;
 //state change
 always@(posedge clk,negedge reset)
    begin
    if(!reset)
    cstate<=0;
    else
    cstate<=nstate;
    end 
  
  //state information  
 
 always@(*)
    begin
    nstate = cstate;
        case(cstate)
            IDLE:begin
                
                if(ena_bram==1'b1 && wea_bram==1'b0)
                    begin
                        if(READ_LATENCY==1)
                        nstate=READ;
                        else
                        nstate=WAIT;
                     end
                   end
              
             WAIT:begin
                if(wait_counter==READ_LATENCY-1)
                    nstate=READ;
                else
                    nstate=WAIT;
                end
                
             READ:begin
                nstate=IDLE;
                end      
      endcase
     end
      
      
      
always@(posedge clk,negedge reset)
    begin
    if(!reset)
    wait_counter<=0;
    else
        begin      
        if(cstate==WAIT)
        wait_counter<=wait_counter+1;
        else
        wait_counter<=0;
        end
     end
 
 
 
always@(*)
    begin
            if(cstate==READ)
            valid=1;
            else
            valid=0;
     end
     
     
     
 always@(*)
    begin
            begin
            if(cstate==WAIT || wea_bram==1)
            enable=1;
            else
            enable=0;
            end
     end
     
     
 assign douta=(valid==1) ? douta_bram:0;
                          
    //make bram
blk_mem_gen_0 bram(
  .clka(clk),    // input wire clka
  .ena(enable),      // input wire ena
  .wea(wea_bram),      // input wire [0 : 0] wea
  .addra(addra),  // input wire [7 : 0] addra
  .dina(dina),    // input wire [31 : 0] dina
  .douta(douta_bram)  // output wire [31 : 0] douta
);
endmodule
