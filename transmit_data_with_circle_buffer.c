#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define CIRC_BUFFER_SIZE 8

typedef struct
{
    uint8_t buffer[CIRC_BUFFER_SIZE];
    uint32_t head;
    uint32_t tail;
} circ_buffer_t;

void uart_transmit(circ_buffer_t* circ_buffer)
{
    for(int i = circ_buffer->tail; i < circ_buffer->head; i++)
    {
        printf("transmited[%d]: %d\n", i, circ_buffer->buffer[i]);
    }
}
void send_data_to_isp(circ_buffer_t* circ_buffer, uint8_t* data, uint32_t length)
{
    uint32_t i = 0;
    uint32_t start_pos = 0;

    do
    {
        for(i = 0; i < CIRC_BUFFER_SIZE; i++)
        {
            if(i == length) break;
            circ_buffer->buffer[i] = data[i + start_pos];
        }

        if(i == length)
        {
            circ_buffer->head = length;
            circ_buffer->tail = 0;
            length = 0;
        }
        else
        {
            circ_buffer->head = CIRC_BUFFER_SIZE;
            circ_buffer->tail = 0;
            start_pos = CIRC_BUFFER_SIZE;
            length = length - CIRC_BUFFER_SIZE;
        }

        printf("===================\n");
        uart_transmit(circ_buffer);

    } while(length > 0);
}

int main()
{
    uint8_t data[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    circ_buffer_t circ_buffer;

    send_data_to_isp(&circ_buffer, data, 15);

    return 0;
}
