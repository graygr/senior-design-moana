import smbus
import time

bus = smbus.SMBus(0)

# i2c address of the arduino we are writing to
address = 0x40

def writeNumber(value):
    bus.write_byte(address, value)
    return -1

def readNumber():
    number = bus.read_byte(address)
    return number


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
print("\nHello, welcome to MOANAINTERFACE (name pending on something better)\n\nWhat mode would you like to operate in?\n\t1. Subsystem debug\n\t2. Scripted operations\n\t3. Mission planner\n\t4. I'm scared and need help")

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
                
                print("Sending command to run thruster at " + speed_param + "%...\n")
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
                print("Sending command to run thruster at " + speed_param + "% for " + dur_param + "ms...\n")
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
                # Find which direction
                print("What direction would you like to set? (1 or 2 - TODO: find out which one is which)")
                dir_param = input("")
                # Find whhat angle
                print("What angle would you like to set? (0-20)")
                ang_param = input("")
                
                print("Sending command to run yaw at " + dir_param + " with angle of " +  ang_param + "...")
                # Build CAN command
                # Write yaw ID
                writeNumber(3)
                # Write yaw direction
                writeNumber(dir_param)
                # Write yaw angle
                writeNumber(ang_param)
                # fill in 4 empty bytes
                for i in range(5):
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
                
                print("Sending command to run thruster at " + speed_param + "%...\n")
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
        print("\nToo bad bud, haven't written anything for this yet. Better luck next time! - last updated 4/21/21")
    else:
        print("\nERROR: Invalid number, please try again with a number between 1 and 4")
    writeNumber(var)
    number = readNumber()
