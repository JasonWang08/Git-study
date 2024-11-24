/*
 * GeekOS C code entry point
 * Copyright (c) 2001,2003,2004 David H. Hovemeyer <daveho@cs.umd.edu>
 * Copyright (c) 2003, Jeffrey K. Hollingsworth <hollings@cs.umd.edu>
 * Copyright (c) 2004, Iulian Neamtiu <neamtiu@cs.umd.edu>
 * $Revision: 1.51 $
 * 
 * This is free software.  You are permitted to use,
 * redistribute, and modify it as specified in the file "COPYING".
 */

#include <geekos/bootinfo.h>
#include <geekos/string.h>
#include <geekos/screen.h>
#include <geekos/mem.h>
#include <geekos/crc32.h>
#include <geekos/tss.h>
#include <geekos/int.h>
#include <geekos/kthread.h>
#include <geekos/trap.h>
#include <geekos/timer.h>
#include <geekos/keyboard.h>




/*
 * Kernel C code entry point.
 * Initializes kernel subsystems, mounts filesystems,
 * and spawns init process.
 */

/*problem 1
void print_key(){ //project0's Code
    Print("Ctrl + D to exit\n");
    while (1) {
        Keycode keycode = Wait_For_Key();
        if (!(keycode & (KEY_SPECIAL_FLAG | KEY_RELEASE_FLAG))) {
            char ascii = keycode & 0xff;
            if ((keycode & KEY_CTRL_FLAG) && ascii == 'd') {
                Print("\nBye!See you next time.\n");
                Exit(0);
            } else {
                Print("%c", ascii == '\r' ? '\n' : ascii);
            }
        }
    }
    //  KEY_SPECIAL_FLAG 0x0100
    //  KEY_KEYPAD_FLAG  0x0200
    //  KEY_SHIFT_FLAG   0x1000
    //  KEY_ALT_FLAG     0x2000
    //  KEY_CTRL_FLAG    0x4000
    //  KEY_RELEASE_FLAG 0x8000
}*/

/*problem 2
static void Print_str1(ulong_t arg)
{
	while(1)
	{
	Print("NW");
	}
}
static void Print_str2(ulong_t arg)
{
	while(1)
	{
	Print("PU");
	}
}
*/

// Problem 3: Create two new kernel threads
static void Print_Countdown(ulong_t arg)
{
    int count = 10;
    while(count > 0)
    {
        Print("Countdown: %d\n", count);
        count--;
        Wait(1000);  // Wait for 1 second
    }
    Print("Countdown finished!\n");
}

static void Print_Alphabet(ulong_t arg)
{
    char letter = 'A';
    while(letter <= 'Z')
    {
        Print("%c ", letter);
        letter++;
        Wait(500);  // Wait for 0.5 seconds
    }
    Print("\nAlphabet printing completed!\n");
}

// Problem 3: Create two new kernel threads to output shapes
static void Print_Triangle(ulong_t arg)
{
    int rows = 5;
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= i; j++) {
            Print("*");
        }
        Print("\n");
    }
    Print("Triangle output completed!\n");
}

static void Print_Square(ulong_t arg)
{
    int size = 4;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Print("# ");
        }
        Print("\n");
    }
    Print("Square output completed!\n");
}

void Main(struct Boot_Info* bootInfo)
{
    Init_BSS();
    Init_Screen();
    Init_Mem(bootInfo);
    Init_CRC32();
    Init_TSS();
    Init_Interrupts();
    Init_Scheduler();
    Init_Traps();
    Init_Timer();
    Init_Keyboard();


    Set_Current_Attr(ATTRIB(BLACK, GREEN|BRIGHT));
    Print("Welcome to GeekOS!\n");
    Set_Current_Attr(ATTRIB(BLACK, GRAY));
    /*struct Kernel_Thread *thread = Start_Kernel_Thread(&print_key, 0, PRIORITY_NORMAL, false);
    if (thread==NULL)
	Print("Error: Failed to start kernel thread.\n");
    else
	Print("Kernel thread started successfully.\n");
	*/
   /* struct Kernel_Thread *thread1= Start_Kernel_Thread(&Print_str1, 0, PRIORITY_NORMAL, false);
    struct Kernel_Thread *thread2= Start_Kernel_Thread(&Print_str2, 0, PRIORITY_NORMAL, false);
    if (thread1== NULL) {
    Print("Error: Failed to start kernel thread1.\n");
} else {
    Print("Kernel thread1 started successfully.\n");
}
    if (thread2== NULL) {
    Print("Error: Failed to start kernel thread2.\n");
} else {
    Print("Kernel thread2 started successfully.\n");
}

    /*TODO("Start a kernel thread to echo pressed keys and print counts");*/

    // Start new kernel threads
    struct Kernel_Thread *thread1 = Start_Kernel_Thread(&Print_Triangle, 0, PRIORITY_NORMAL, false);
    struct Kernel_Thread *thread2 = Start_Kernel_Thread(&Print_Square, 0, PRIORITY_NORMAL, false);

    if (thread1 == NULL) {
        Print("Error: Failed to start triangle thread.\n");
    } else {
        Print("Triangle thread started successfully.\n");
    }

    if (thread2 == NULL) {
        Print("Error: Failed to start square thread.\n");
    } else {
        Print("Square thread started successfully.\n");
    }

    /* Now this thread is done. */
    Exit(0);
}
