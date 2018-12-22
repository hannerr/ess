#include <UART_Task.h>
#include <mailbox.h>


// create mailbox for outgoing stuff - sensor 2 uart for example
uint8_t _createMailbox(Mailbox_Handle* mbox){
    // 119
    Mailbox_Params mboxParams;
    Error_Block eb;
    Error_init(&eb);

    Mailbox_Params_init(&mboxParams);
    *mbox = Mailbox_create(sizeof(complex_msg), 5, &mboxParams, &eb);
    if (mbox == NULL) {
        System_abort("Mailbox create failed");
    }
    return 0;
}

// create channel from handle 2 led
void createMailboxIn(){
    if(_createMailbox(&mboxIn)!=0){
        System_abort("Mailbox create failed");
    }
}

// comm channel from temp 2 manager
void createMailbox(){
    // create mbox for
    if(_createMailbox(&mbox)!=0){
        System_abort("Mailbox create failed");
    }
}


// create a mailbox from pc 2 board
void createMailboxPC2UART(){
    if(_createMailbox(&mboxPC2UART)!=0){
        System_abort("Mailbox create failed");
    }
}

// create a mailbox from board 2 pc - print
void createMailboxUART2PC(){
    if(_createMailbox(&mboxUART2PC)!=0){
        System_abort("Mailbox create failed");
    }
}

// set up 2 tasks for 2 mailboxes - incoming and outgoing
void setup_Mailbox_Task(){
    // set up a mailbox task for get values from the sensor (hut21d > mailbox)
    Task_Params taskMailbox;
    Task_Handle taskMbox;
    Error_Block eb;

    // Create blink task with priority 15
    Error_init(&eb);
    Task_Params_init(&taskMailbox);
    taskMailbox.stackSize = 1024; // stack in bytes
    taskMailbox.priority = 14; // 0-15 (15 is highest priority on default -> see RTOS Task configuration)
    //taskMailbox.arg0 = mbox;
    // legt den task neu an - task function mit 2 aufrufparameter
    taskMbox = Task_create((Task_FuncPtr)createMailbox, &taskMailbox, &eb);
    if (taskMbox == NULL) {
        System_abort("TaskMbox create failed");
    }
    System_printf("TaskMbox create success");
}

// create mailbox
void setup_MailboxIN_Task(){

    // set up a mailbox task for get values from the sensor (mailbox > color)
    Task_Params taskMailboxIn;
    Task_Handle taskMboxIn;
    Error_Block ebIn;

    // Create blink task with priority 15
    Error_init(&ebIn);
    Task_Params_init(&taskMailboxIn);
    taskMailboxIn.stackSize = 1024; // stack in bytes
    taskMailboxIn.priority = 14; // 0-15 (15 is highest priority on default -> see RTOS Task configuration)
    //taskMailbox.arg0 = mboxIn;
    // legt den task neu an - task function mit 2 aufrufparameter
    taskMboxIn = Task_create((Task_FuncPtr)createMailboxIn, &taskMailboxIn, &ebIn);
    if (taskMboxIn == NULL) {
        System_abort("TaskMbox create failed");
    }
}

// create mailbox
void setup_Mailbox_Uart2PC_Task(){

    // set up a mailbox task for get values from the sensor (mailbox > color)
    Task_Params taskParams;
    Task_Handle taskHandle;
    Error_Block ebIn;

    // Create blink task with priority 15
    Error_init(&ebIn);
    Task_Params_init(&taskParams);
    taskParams.stackSize = 1024; // stack in bytes
    taskParams.priority = 14; // 0-15 (15 is highest priority on default -> see RTOS Task configuration)
    //taskMailbox.arg0 = mboxIn;
    // legt den task neu an - task function mit 2 aufrufparameter
    taskHandle = Task_create((Task_FuncPtr)createMailboxUART2PC, &taskParams, &ebIn);
    if (taskHandle == NULL) {
        System_abort("TaskMbox create failed");
    }
}

// create mailbox
void setup_Mailbox_PC2Uart_Task(){

    // set up a mailbox task for get values from the sensor (mailbox > color)
    Task_Params taskParams;
    Task_Handle taskHandle;
    Error_Block ebIn;

    // Create blink task with priority 15
    Error_init(&ebIn);
    Task_Params_init(&taskParams);
    taskParams.stackSize = 1024; // stack in bytes
    taskParams.priority = 14; // 0-15 (15 is highest priority on default -> see RTOS Task configuration)
    //taskMailbox.arg0 = mboxIn;
    // legt den task neu an - task function mit 2 aufrufparameter
    taskHandle = Task_create((Task_FuncPtr)createMailboxPC2UART, &taskParams, &ebIn);
    if (taskHandle == NULL) {
        System_abort("TaskMbox create failed");
    }
}

