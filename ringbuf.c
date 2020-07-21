#include <stdio.h>
typedef unsigned short uint16_t;
#define MAX_BUFFER_SIZE 10
#define UART_BUF_SIZE  10

#define WANTED_APP_DATA (UART_BUF_SIZE)


//declare three arrays
int app_data[WANTED_APP_DATA] = {0};
int uart_gend_data[UART_BUF_SIZE] = {0};
int ring_buf[MAX_BUFFER_SIZE] = {0};

uint16_t front_pointer_pos,rear_pointer_pos;

void ringbuf_init(void)
{
    front_pointer_pos = 9;
    rear_pointer_pos = 9;
}

void write_buffer(void)
{
    if((rear_pointer_pos+1)%MAX_BUFFER_SIZE != front_pointer_pos)
    {
        ring_buf[rear_pointer_pos] = uart_gend_data[rear_pointer_pos];
        rear_pointer_pos = (rear_pointer_pos+1)%MAX_BUFFER_SIZE;
    }else{
        printf("ringbuffer is full!\n");
    }
}

void read_buffer(void)
{
    app_data[front_pointer_pos] = ring_buf[front_pointer_pos];
    if(front_pointer_pos != rear_pointer_pos)
    {
        front_pointer_pos = (front_pointer_pos+1)%MAX_BUFFER_SIZE;
    }
}

void printappdata(int n)
{
    for(int i = 0;i<n;i++)
    {
        printf("%d\n",*(app_data+i));
    }
}

void gen_uart_data(int n)
{
    for(int i = 0;i<n;i++)
    {
        uart_gend_data[i] = (i+1)*(i+1);
    }
}
void check_ringbuffer_status()
{
        if(front_pointer_pos == rear_pointer_pos)
        {
            printf("queue is empty!\n");
        }else if((rear_pointer_pos+1)%MAX_BUFFER_SIZE == front_pointer_pos)
        {
            printf("queue is full!,rear_pointer_pos is %d,front_pointer_pos is %d\n",rear_pointer_pos,front_pointer_pos);
        }else{
            printf("queue is working normally!\n");
        }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    //init ringbuffer
    ringbuf_init();
    
    //generate the uart data
    gen_uart_data(MAX_BUFFER_SIZE);
    
    //write buffer
    for(int i=0;i<(MAX_BUFFER_SIZE);i++)
        {
            check_ringbuffer_status();
            write_buffer();
           // printf("rear_pointer_pos position is %d\n",rear_pointer_pos);
            //printf("front_pointer_pos position is %d\n",front_pointer_pos);
            
        }
    
    //read buffer
    for(int i=0;i<(MAX_BUFFER_SIZE-9);i++)
        {
            read_buffer();
            check_ringbuffer_status();
        }
    
    //print app data
    printappdata(WANTED_APP_DATA);
    return 0;
}