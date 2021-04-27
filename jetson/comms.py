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
print("\nHello, welcome to MOANAINTERFACE (name pending on something better)\n\nWhat mode would you like to operate in?\n\t1. Subsystem debug\n\t2. Scripted operations\n\t3. Mission planner\n\t4. I'm scared and need help")

while True:
    var = input("")
    if not var:
        continue
    # Python is very dumb in switch statements so here goes the if else chain
    
    # This selection will control the debug mode
    # Debug mode will allow the user to build individual commands to each subsystem and send them for testing and integration purposes 
    if(var == 1):
        print("\nEntering debug mode...\n")
        #TODO: write out step by step can message building to bugtest subsystem messaging
        print("\nWhat subsystem do you want to test?\n\t1. Thruster\n\t2. Yaw Control\n\t3. Pitch Control\n\t4. Depth Control\n\t5. ") 
    elif(var == 2):
        print("\nEntering scripted mission mode...\n")
        #TODO: write out 2-3 preplanned missions for initial testing in the field
    elif(var == 3):
        print("\nEntering mission planner mode...\n")
        #TODO: might leave this for next year?
    elif(var == 4):
        print("\nToo bad bud, haven't written anything for this yet. Better luck next time! - last updated 4/21/21")
    else:
        print("\nERROR: Invalid number, please try again with a number between 1 and 4")
    writeNumber(var)
    number = readNumber()
