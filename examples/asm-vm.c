#include <🤑.h>
#include <🤐.h>
#include <🤥.h>
#include <👻.h>
#include <👂/🤷‍♀️.h>
#include <👂/👨‍🚒.h>
#include <👂/💆.h>
#include <👂/⛷.h>
#include <🐫.h>
#include <🐼.h>
#include <🌿.h>
🧀{
    🍔_🌍=0,
    🍔_🚊,
    🍔_🎄,
    🍔_🔒,
    🍔_🛁,
    🍔_🍎,
    🍔_🐔,
    🍔_🙇,
    🍔_🙅,
    🍔_🎅,
    🍔_👶
}🧀{
    🥚_🕋=0,
    🥚_🚚,
    🥚_🤵,
    🥚_🔰,
    🥚_👄,
    🥚_⚾,
    🥚_👩‍💻,
    🥚_👊,
    🥚_🐀,
    🥚_🌒,
    🥚_🚲,
    🥚_💊,
    🥚_👁️‍🗨️,
    🥚_✨,
    🥚_💅,
    🥚_👃
}🧀{
    🍴_💯=1<<0,
    🍴_💛=1<<1,
    🍴_🙊=1<<2,
}🧀{
    😻_😹=0xFE00,
    😻_👺=0xFE02
}🧀{
    👃_GETC=0x20,
    👃_OUT=0x21,
    👃_PUTS=0x22,
    👃_IN=0x23,
    👃_PUTSP=0x24,
    👃_HALT=0x25
}
💤 memory[UINT16_MAX];
💤 reg[🍔_👶];
💤 sign_extend(💤 x,int bit_count){
    if((x>>(bit_count-1))&1){
        x |= (0xFFFF<<bit_count);
    }
    return(x);
}
💤 swap16(💤 x){
    return(x<<8)|(x>>8);
}
void update_flags(💤 r){
    if(reg[r]==0){
        reg[🍔_🎅]=🍴_💛;
    }else if(reg[r]>>15){
        reg[🍔_🎅]=🍴_🙊;
    }else{
        reg[🍔_🎅]=🍴_💯;
    }
}
void read_image_file(FILE* file){
    💤 origin;
    fread(&origin,sizeof(origin),1,file);
    origin=swap16(origin);
    💤 max_read=UINT16_MAX-origin;
    💤* p=memory+origin;
    size_t read=fread(p,sizeof(💤),max_read,file);
    while(read-- >0){
        *p=swap16(*p);
        ++p;
    }
}
int read_image(const char* image_path){
    FILE* file=fopen(image_path,"rb");
    if(!file){return(0);};
    read_image_file(file);
    fclose(file);
    return(1);
}
💤 check_key(){
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO,&readfds);
    struct timeval timeout;
    timeout.tv_sec=0;
    timeout.tv_usec=0;
    return select(1,&readfds,NULL,NULL,&timeout)!=0;
}
void mem_write(💤 address,💤 val){
    memory[address]=val;
}
uint16_t mem_read(💤 address){
    if(address==😻_😹){
        if(check_key()){
            memory[😻_😹]=(1<<15);
            memory[😻_👺]=getchar();
        }else{
            memory[😻_😹]=0;
        }
    }
    return memory[address];
}
struct termios original_tio;
void disable_input_buffering(){
    tcgetattr(STDIN_FILENO,&original_tio);
    struct termios new_tio=original_tio;
    new_tio.c_lflag&=~ICANON&~ECHO;
    tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
}
void restore_input_buffering(){
    tcsetattr(STDIN_FILENO,TCSANOW,&original_tio);
}
void handle_interrupt(int signal){
    restore_input_buffering();
    printf("\n");
    exit(-2);
}
int main(int argc,const char* argv[]){
    if(argc<2){
        printf("vomit lmao [image-file1] ...\n");
        exit(2);
    }
    for(int j=1;j<argc;++j){
        if(!read_image(argv[j])){
            printf("your iso failed, retard.: %s\n",argv[j]);
            exit(1);
        }
    }
    signal(SIGINT,handle_interrupt);
    disable_input_buffering();
    🧀{🙅_START=0x3000};
    reg[🍔_🙅]=🙅_START;
    int running=1;
    while(running){
        💤 instr=mem_read(reg[🍔_🙅]++);
        💤 op=instr>>12;
        switch(op){
            case OP_🚚:{
                    💤 r0=(instr>>9)&0x7;
                    💤 r1=(instr>>6)&0x7;
                    💤 imm_flag=(instr>>5)&0x1;
                    if(imm_flag){
                        💤 imm5=sign_extend(instr&0x1F,5);
                        reg[r0]=reg[r1]+imm5;
                    }else{
                        💤 r2=instr&0x7;
                        reg[r0]=reg[r1]+reg[r2];
                    }
                    update_flags(r0);
                }
                break;
            case 🥚_⚾:{
                    💤 r0=(instr>>9)&0x7;
                    💤 r1=(instr>>6)&0x7;
                    💤 imm_flag=(instr>>5)&0x1;
                    if(imm_flag){
                        💤 imm5=sign_extend(instr&0x1F,5);
                        reg[r0]=reg[r1]&imm5;
                    }else{
                        💤 r2=instr&0x7;
                        reg[r0]=reg[r1]&reg[r2];
                    }
                    update_flags(r0);
                }
                break;
            case 🥚_🌒:
                {
                    💤 r0=(instr>>9)&0x7;
                    💤 r1=(instr>>6)&0x7;
                    reg[r0]=~reg[r1];
                    update_flags(r0);
                }
                break;
            case 🥚_🕋:{
                    💤 pc_offset=sign_extend((instr)&0x1ff,9);
                    💤 cond_flag=(instr>>9)&0x7;
                    if(cond_flag&reg[🍔_🎅]){
                        reg[🍔_🙅]+=pc_offset;
                    }
                }
                break;
            case 🥚_👁️‍🗨️:
                {
                    💤 r1=(instr>>6)&0x7;
                    reg[🍔_🙅]=reg[r1];
                }
                break;
            case 🥚_👄:
                {
                    💤 r1=(instr>>6)&0x7;
                    💤 long_pc_offset=sign_extend(instr&0x7ff,11);
                    💤 long_flag=(instr>>11)&1;
                    reg[🍔_🙇]=reg[🍔_🙅];
                    if(long_flag){
                        reg[🍔_🙅]+=long_pc_offset;
                    }
                    else{
                        reg[🍔_🙅]=reg[r1];
                    }
                    break;
                }
                break;
            case 🥚_🤵:
                {
                    💤 r0=(instr>>9)&0x7;
                    💤 pc_offset=sign_extend(instr&0x1ff,9);
                    reg[r0]=mem_read(reg[🍔_🙅]+pc_offset);
                    update_flags(r0);
                }
                break;
            case 🥚_🚲:
                {
                    💤 r0=(instr>>9)&0x7;
                    💤 pc_offset=sign_extend(instr&0x1ff,9);
                    reg[r0]=mem_read(mem_read(reg[🍔_🙅]+pc_offset));
                    update_flags(r0);
                }
                break;
            case 🥚_👩‍💻:
                {
                    💤 r0=(instr>>9)&0x7;
                    💤 r1=(instr>>6)&0x7;
                    💤 offset=sign_extend(instr&0x3F,6);
                    reg[r0]=mem_read(reg[r1]+offset);
                    update_flags(r0);
                }
                break;
            case 🥚_💅:
                {
                    💤 r0=(instr>>9)&0x7;
                    💤 pc_offset=sign_extend(instr&0x1ff,9);
                    reg[r0]=reg[🍔_🙅]+pc_offset;
                    update_flags(r0);
                }
                break;
            case 🥚_🔰:
                {
                    💤 r0=(instr>>9)&0x7;
                    💤 pc_offset=sign_extend(instr&0x1ff,9);
                    mem_write(reg[🍔_🙅]+pc_offset,reg[r0]);
                }
                break;
            case 🥚_💊:
                {
                    💤 r0=(instr>>9)&0x7;
                    💤 pc_offset=sign_extend(instr&0x1ff,9);
                    mem_write(mem_read(reg[🍔_🙅]+pc_offset),reg[r0]);
                }
                break;
            case 🥚_👊:
                {
                    💤 r0=(instr>>9)&0x7;
                    💤 r1=(instr>>6)&0x7;
                    💤 offset=sign_extend(instr&0x3F,6);
                    mem_write(reg[r1]+offset,reg[r0]);
                }
                break;
            case 🥚_👃:
                switch(instr&0xFF){
                    case 👃_GETC:
                        reg[🍔_🌍]=(💤)getchar();
                        break;
                    case 👃_OUT:
                        putc((char)reg[🍔_🌍],stdout);
                        fflush(stdout);
                        break;
                    case 👃_PUTS:
                        {
                            💤* c=memory+reg[🍔_🌍];
                            while(*c){
                                putc((char)*c,stdout);
                                ++c;
                            }
                            fflush(stdout);
                        }
                        break;
                    case 👃_IN:
                        printf("Enter a character: ");
                        char c=getchar();
                        putc(c,stdout);
                        reg[🍔_🌍]=(💤)c;
                        break;
                    case 👃_PUTSP:
                        {
                            💤* c=memory+reg[🍔_🌍];
                            while (*c){
                                char char1=(*c)&0xFF;
                                putc(char1,stdout);
                                char char2=(*c)>>8;
                                if(char2)putc(char2,stdout);
                                ++c;
                            }
                            fflush(stdout);
                        }
                        break;
                    case 👃_HALT:
                        puts("boop");
                        fflush(stdout);
                        running=0;
                        break;
                }
                break;
            case 🥚_✨:
            case 🥚_🐀:
            default:
                abort();
                break;
        }
    }
    restore_input_buffering();
}
