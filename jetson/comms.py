import smbus
import time
import sys
import csv
import time
import os

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
    print("\nHello, welcome to Toucan, the CLI Interface to MOANA\nWhat mode would you like to operate in?\n\t1. Subsystem debug\n\t2. Scripted operations\n\t3. Mission planner\n\t4. Manual Input\n\t5. Exit Program")

    ui_input = input("")
    if not ui_input:
        continue
    # Python is very dumb in switch statements so here goes the if else chain
    
    # This selection will control the debug mode
    
    # Debug mode will allow the user to build individual commands to each subsystem and send them for testing and integration purposes 
    if(ui_input == 1):
        print("\nEntering debug mode...\n")
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
        print("Please pick from the current list of missions below: ")
        
        # Use the OS library to walk through the list of files in the missions folder and print them out
        counter = 1
        # TODO: might have to store files outside the scope of this for loop
        # TODO: test on jetson to see what code I have to run to get the list of files
        for dirpath, dirnames, files in os.walk('missions'):
            for file_name in files:
                print("\t" + str(counter) + ". " + file_name)
                counter = counter + 1

        # Ask user to select which file they want to execute
        print("\nWhich script would you like to execute?")
        script_input = input("")

        # Open file at that index
        # TODO: this is temp until I can run on the jetson, find out how to open file index and build path out to open
        with open("missions/" + files[script_input - 1]) as csvfile:
            screader = csv.reader(csvfile, delimiter=',')
            line_no = 0
            for row in screader:
                # On even rows, send commands
                if line_no % 2 == 0:
                    # Read in each row and send the command, then wait the specified delay
                    for element in row:
                        writeNumber(element)
                # On odd rows, read in the time delay
                else:
                    time.sleep(row[0])
                # Increment line number
                line_no = line_no + 1 
        print("Script ended. If the vehicle is unrecoverable at this point, best of luck!")
        continue

    elif(ui_input == 3):
        print("\nEntering mission planner mode...\n")
        print("What would you like to name this script?")
        # In python2, need raw input. Otherwise, tries to run string as python code
        name_input = raw_input("")

        cmd_arr = [None] * 8

        # TODO: make sure that this works
        with open("missions/" + str(name_input) + ".csv", mode='w') as csv_file:
            csv_writer = csv.writer(csv_file, delimiter = ",")
            while(1):
                print("What subsystem do you want to command?\n\t1. Thruster\n\t2. Yaw Control\n\t3. Depth Control\n\t4. Pitch Control\n\t5. Exit")
                sys_in = input("")

                if(sys_in == 1):
                    # Build thruster command
                    print("Building thruster command...\nWhat would you like to do with the thruster?\n\t1. Turn on at set speed\n\t2. Turn off\n\t3. Turn on at set speed for set time\n\t4. Go back")
                    cmd_param = input("")
                    if(cmd_param == 1):
                        # Turn thruster on to user defined speed
                        print("What speed would you like? (0-100)")
                        speed_param = input("")
                        # Write thruster ID
                        cmd_arr[0] = 2
                        # Write thruster direction, 1 for backwards 2 for forwards
                        cmd_arr[1] = 2
                        # Write thruster speed
                        cmd_arr[2] = speed_param
                        # Write default duration (0 - run until stop)
                        cmd_arr[3] = 0 
                        # fill in 5 empty bytes
                        cmd_arr[4] = -1
                        cmd_arr[5] = -1
                        cmd_arr[6] = -1
                        cmd_arr[7] = -1

                        
                    elif(cmd_param == 2):
                        # Turn thruster off

                        # Write thruster ID
                        cmd_arr[0] = 2
                        # Write thruster direction
                        cmd_arr[1] = 1
                        # Write thruster speed
                        cmd_arr[2] = 0
                        # Write default duration (0 - run until stop)
                        cmd_arr[3] = 0
                        # fill in 4 empty bytes
                        cmd_arr[4] = -1
                        cmd_arr[5] = -1
                        cmd_arr[6] = -1
                        cmd_arr[7] = -1

                    elif(cmd_param == 3):
                        # Turn thruster on to user defined speed for user defined duration
                        print("What speed would you like? (0-100)")
                        speed_param = input("")
                        print("What duration would you like?")
                        dur_param = input("")
                        
                        # Write thruster ID
                        cmd_arr[0] = 2
                        # Write thruster direction
                        cmd_arr[1] = 2
                        # Write thruster speed
                        cmd_arr[2] = speed_param
                        # Write default duration (0 - run until stop)
                        cmd_arr[3] = dur_param
                        # fill in 4 empty bytes
                        cmd_arr[4] = -1
                        cmd_arr[5] = -1
                        cmd_arr[6] = -1
                        cmd_arr[7] = -1
                    
                    elif(cmd_param == 4):
                        # Skip back to start of loop
                        continue
                elif(sys_in == 2):
                    # Build yaw command
                    print("Building yaw command...\nWhat would you like to do with it?\n\t1. Set to defined angle\n\t2. Go back")
                    cmd_param = input("")
                    if(cmd_param == 1):
                        # Find what angle
                        print("What angle would you like to set? (0-20)")
                        ang_param = input("")
                        
                        print("Would you like positive or negative direction? (1 for neg, 2 for pos)")
                        dir_param = input("")

                        # Build CAN command
                        # Write yaw ID
                        cmd_arr[0] = 3
                        # Write yaw angle
                        cmd_arr[1] = ang_param
                        # positive or negative
                        cmd_arr[2] = dir_param 
                        # fill in empty bytes
                        cmd_arr[3] = -1
                        cmd_arr[4] = -1
                        cmd_arr[5] = -1
                        cmd_arr[6] = -1
                        cmd_arr[7] = -1

                    elif(cmd_param == 2):
                        print("Returning...\n")
                        continue
                
                # Build depth control command (CURRENTLY UNFINISHED SYSTEM, TODO: Fill in once implemented)
                elif(sys_in == 3):
                    print("This subsystem is currently unfinished, please try annother option")
                    continue
                
                # Build pitch control command
                elif(sys_in == 4): 
                    print("Building pitch command...\nWhat would you like to do with it?\n\t1. Set to defined angle\n\t2. Go back")
                    cmd_param = input("")

                    if(cmd_param == 1):
                        # Store pitch control id
                        cmd_arr[0] = 5
                        # Store direction of pitch
                        print("Positive or negative pitch angle? (1 for neg, 2 for pos)")
                        pitch_dir = input("")
                        cmd_arr[1] = pitch_dir
                        # Store angle of pitch (0-12)
                        print("What angle? (0-12 degrees)")
                        pitch_ang = input("")
                        cmd_arr[2] = pitch_ang
                        cmd_arr[3] = -1
                        cmd_arr[4] = -1
                        cmd_arr[5] = -1
                        cmd_arr[6] = -1
                        cmd_arr[7] = -1

                    elif(cmd_param == 2):
                        print("Returning to menu...\n")
                        continue

                # Break out of command builder
                elif(sys_in == 5):
                    break

                # Store command, then store delay
                csv_writer.writerow(cmd_arr)
                print("What delay would you like (seconds)?\n")
                time_del = input("")
                csv_writer.writerow([time_del]) 

    elif(ui_input == 4):
        print("Reading raw input. Type any number other than -1 to send to CAN. Every 8 character a CAN message is sent. Type -1 to exit")
        cmd_buf = [None] * 8
        cmd_input = input("")
        counter = 0
        while(cmd_input != -1):
            cmd_buf[counter % 8] = cmd_input
            counter += 1
            print("current cmd buffer: " + str(cmd_buf[0]) + " " + str(cmd_buf[1]) + " " + str(cmd_buf[2]) + " " + str(cmd_buf[3]) + " " + str(cmd_buf[4]) + " " + str(cmd_buf[5]) + " " + str(cmd_buf[6]) + " " + str(cmd_buf[7]))
            
            if((counter) % 8 == 0 and counter != 0):
                print("Sending command: " + str(cmd_buf[0]) + " " + str(cmd_buf[1]) + " " + str(cmd_buf[2]) + " " + str(cmd_buf[3]) + " " + str(cmd_buf[4]) + " " + str(cmd_buf[5]) + " " + str(cmd_buf[6]) + " " + str(cmd_buf[7]))
                print("Type 1 to confirm, 2 to deny and reset the buffer")
                confirm_var = input("")
                if(confirm_var == 1):
                    for i in range(8):
                        writeNumber(cmd_buf[i])
                    print("Reading raw input. Type any number other than -1 to send to CAN. Every 8 character a CAN message is sent. Type -1 to exit")
        
                if(confirm_var == 2):
                    for i in range(8):
                        cmd_buf[i] = [None]
                    print("Reading raw input. Type any number other than -1 to send to CAN. Every 8 character a CAN message is sent. Type -1 to exit")
            cmd_input = input("")
                
    elif(ui_input == 5):
        print("Have a nice day!")
        exit()
    else:
        print("\nERROR: Invalid number, please try again with a number between 1 and 5")
    
