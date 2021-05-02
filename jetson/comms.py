import smbus
import time
import sys
# import thread
import time

bus = smbus.SMBus(0)

# i2c address of the arduino we are writing to
address = 0x40

def writeNumber(value):
    bus.write_byte(address, value)
    return -1

# # Function to run on thread to listen to anything coming over the I2C Bus
# def readBus(threadName):
#     while 1:
#         # TODO: Format the arduino code to write back the data in readable format
#         number = bus.read_byte(address)
#         # TODO: Store each line of CAN communication into array and append to CSV. Print for now
#         print("Reading CAN data from thread: ")
#         print(number)


print("#########################################################################################")
print("#        <><     <><          <><              <><           o <><   o          <><     #")
print("#       ________________________________       o  o                   <><         <><   #")
print("#      /                                \      o   o     Santa Clara University         #")
print("#     /  O                               \  o   o        Senior Design 2021   <><       #")
print("#    < ____/        M O A N A             >X  o          Made with love by:       <><   #")
print("#     \                                  /  o                 Gregor Limstrom           #")
print("#      \________________________________/       <><       <><       Andrew Kambe        #")
print("#                  <><       <><           <><          <><      <><    and friends :D  #")
print("#             <><     <><      <><           <><      <><       <><      <><            #")
print("#         <><            <><       <><          <><     <><       ><>              <><  #")
print("#########################################################################################")

while True:
    # thread.start_new_thread(readBus)
    print("\nHello, welcome to Toucan, the CLI Interface to MOANA\nWhat mode would you like to operate in?\n\t1. Subsystem debug\n\t2. Scripted operations\n\t3. Mission planner\n\t4. Manual Input")

    ui_input = input("")
    if not ui_input:
        continue
    # Python is very dumb in switch statements so here goes the if else chain
    
    # This selection will control the debug mode
    
    # Debug mode will allow the user to build individual commands to each subsystem and send them for testing and integration purposes 
    if(ui_input == 1):
        print("\nEntering debug mode...\n")
        #TODO: write out step by step can message building to bugtest subsystem messaging
        print("\nWhat subsystem do you want to test?\n\t1. Thruster\n\t2. Yaw Control\n\t3. Depth Control\n\t4. Pitch Control")
        cmd_input = input("")
        if(cmd_input == 1):
            # Build thruster command
            print("Building thruster command...\nWhat would you like to do with the thruster?\n\t1. Turn on at set speed\n\t2. Turn off\n\t3. Turn on at set speed for set time\n\t4. Go back")
            cmd_param = input("")
            if(cmd_param == 1):
                # Turn thruster on to user defined speed
                print("What speed would you like? (0-100)")
                speed_param = input("")
                # Build CAN command
                # Add thruster ID
                # Add data parameters
                
                #print("Sending command to run thruster at " + speed_param + "%...\n")
                # Write thruster ID
                writeNumber(2)
                # Write thruster direction
                writeNumber(1)
                # Write thruster speed
                writeNumber(speed_param)
                # Write default duration (0 - run until stop)
                writeNumber(0)
                # fill in 5 empty bytes
                for i in range(4):
                      writeNumber(-1)
                
            elif(cmd_param == 2):
                # Turn thruster off
                print("Sending shutoff command...\n")
                # Build CAN command
                # Write thruster ID
                writeNumber(2)
                # Write thruster direction
                writeNumber(1)
                # Write thruster speed
                writeNumber(0)
                # Write default duration (0 - run until stop)
                writeNumber(0)
                # fill in 4 empty bytes
                for i in range(4):
                      writeNumber(-1)
                
            elif(cmd_param == 3):
                # TODO: Implement duration command for thruster
                # Turn thruster on to user defined speed for user defined duration
                print("What speed would you like? (0-100)")
                speed_param = input("")
                print("What duration would you like? (TODO: not sure how kambe is implementing this yet)")
                dur_param = input("")
                
                # Build CAN command
                # Add thruster ID
                # Add data parameters
                #print("Sending command to run thruster at " + speed_param + "% for " + dur_param + "ms...\n")
                # Write thruster ID
                writeNumber(2)
                # Write thruster direction
                writeNumber(1)
                # Write thruster speed
                writeNumber(speed_param)
                # Write default duration (0 - run until stop)
                writeNumber(dur_param)
                # fill in 4 empty bytes
                for i in range(4):
                      writeNumber(-1)
            
            elif(cmd_param == 4):
                # Skip back to start of loop
                continue
        elif(cmd_input == 2):
            # Build yaw command
            print("Building yaw command...\nWhat would you like to do with it?\n\t1. Set to defined angle\n\t2. Go back")
            cmd_param = input("")
            if(cmd_param == 1):
                # Find whhat angle
                print("What angle would you like to set? (0-20)")
                ang_param = input("")
                
                # Build CAN command
                # Write yaw ID
                writeNumber(3)
                # Write yaw angle
                writeNumber(ang_param)
                # fill in 4 empty bytes
                for i in range(6):
                      writeNumber(-1)
                
            elif(cmd_param == 2):
                print("Sending reset command now...\n")
                # Write yaw ID
                writeNumber(3)
                # Write yaw direction
                writeNumber(1)
                # Write yaw angle
                writeNumber(0)
                # fill in 4 empty bytes
                for i in range(5):
                      writeNumber(-1)
                
            elif(cmd_param == 3):
                # Return to main menu
                continue
          
        # TODO: build out depth, figure out what commands and how to send them. Not do right now
        elif(cmd_input == 3):
            # TODO: Build depth command
            print("This is currently unfinished, please try annother option")
            continue
            #print("Building depth command...\nWhat would you like to do with it?\n\t1. Set to defined ???\n\t2. Go back")
            cmd_param = input("")
            if(cmd_param == 1):
                
                print("Sending command to run depth at ???...")
                # Build CAN command
                # Write depth ID
                writeNumber(4)
                # Write yaw direction
                writeNumber(dir_param)
                # Write yaw angle
                writeNumber(ang_param)
                # fill in 4 empty bytes
                for i in range(5):
                      writeNumber(-1)
                
                #print("Sending command to run thruster at " + speed_param + "%...\n")
                # Write thruster ID
                writeNumber(2)
                # Write thruster direction
                writeNumber(1)
                # Write thruster speed
                writeNumber(speed_param)
                # Write default duration (0 - run until stop)
                writeNumber(0)
                # fill in 5 empty bytes
                for i in range(4):
                      writeNumber(-1)
                
            elif(cmd_input == 2):
                continue
                
    elif(ui_input == 2):
        print("\nEntering scripted mission mode...\n")
        print("\nThis feature is currently not implemented, please check back later...\n")
        continue
        #TODO: write out 2-3 preplanned missions for initial testing in the field
    elif(ui_input == 3):
        print("\nEntering mission planner mode...\n")
        print("\nThis feature is currently not implemented, please check back later...\n")
        continue
        #TODO: might leave this for next year?
    elif(ui_input == 4):
        print("Reading raw input. Type any number other than -1 to send to CAN. Every 8 character a CAN message is sent. Type -1 to exit")
        cmd_input = input("")
        cmd_buf = [None] * 8
        counter = 0
        while(cmd_input != -1):
            cmd_buf[counter % 8] = cmd_input
            counter += 1
            print("current cmd buffer: " + str(cmd_buf[0]) + " " + str(cmd_buf[1]) + " " + str(cmd_buf[2]) + " " + str(cmd_buf[3]) + " " + str(cmd_buf[4]) + " " + str(cmd_buf[5]) + " " + str(cmd_buf[6]) + " " + str(cmd_buf[7]))
            
            if((counter + 1) % 8 == 0 and counter != 0):
                print("Sending command: ")
                # TODO: Write confirmation and print out cmd_buf
                for i in range(8):
                    writeNumber(cmd_buf[i])

            cmd_input = input("")

            # Data log TODO: Figure out how to log data
#             sys.stdout = open("out.txt","a")
#             print (readNumber())
#             sys.stdout.close()
    else:
        print("\nERROR: Invalid number, please try again with a number between 1 and 4")
    
    number = readNumber()
