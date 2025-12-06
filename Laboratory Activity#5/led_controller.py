import serial
import time
import os

# CONFIGURATION
# REPLACE 'COM3' with your actual port (e.g., 'COM3' on Windows, '/dev/ttyUSB0' on Mac/Linux)
ARDUINO_PORT = 'COM7' 
BAUD_RATE = 9600

def initialize_connection():
    try:
        ser = serial.Serial(ARDUINO_PORT, BAUD_RATE, timeout=1)
        time.sleep(2) # Wait for connection to stabilize
        return ser
    except serial.SerialException:
        print(f"Error: Could not open port {ARDUINO_PORT}. Please check your connection.")
        return None

def clear_screen():
    # Nice to have: Clear screen logic based on OS
    if os.name == 'nt':
        os.system('cls')
    else:
        os.system('clear')

def print_menu():
    clear_screen()
    print("=============================")
    print("   ARDUINO LED CONTROLLER    ")
    print("=============================")
    print("[R] Red ON/OFF")
    print("[G] Green ON/OFF")
    print("[B] Blue ON/OFF")
    print("[A] All ON")
    print("[O] All OFF")
    print("[X] Exit")
    print("=============================")

def main():
    ser = initialize_connection()
    if not ser:
        return

    while True:
        print_menu()
        user_input = input("Enter selection: ").strip().upper()

        if user_input == 'X':
            print("Exiting application...")
            ser.close()
            break
        
        elif user_input in ['R', 'G', 'B', 'A', 'O']:
            # Send data to Arduino
            ser.write(user_input.encode())
            print(f"Command '{user_input}' sent.")
            time.sleep(0.5) # Short pause so user can see the confirmation before screen clears
        
        else:
            print("Invalid input! Please try again.")
            time.sleep(1)

if __name__ == "__main__":
    main()