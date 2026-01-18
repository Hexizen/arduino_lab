import serial
import time
import requests
import sys

# --- CONFIGURATION ---
# UPDATE THIS to match your Arduino's port (e.g., 'COM3', '/dev/ttyACM0')
SERIAL_PORT = 'COM7' 
BAUD_RATE = 9600
API_BASE_URL = "http://172.20.10.3:8000"

def main():
    print(f"--- IoT Client Started ---")
    print(f"Listening on: {SERIAL_PORT}")
    print(f"Target API: {API_BASE_URL}")
    print("Press Ctrl+C to exit.\n")

    ser = None

    try:
        # Initialize Serial Connection
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        time.sleep(2) # Wait for Arduino to reset/stabilize
        
        while True:
            try:
                # 1. Listen to Serial Port
                if ser.in_waiting > 0:
                    # Read line, decode bytes to string, and strip whitespace/newlines
                    incoming_data = ser.readline().decode('utf-8').strip()
                    
                    # Validate that we received data
                    if incoming_data:
                        group_number = incoming_data
                        
                        # Feedback: Group Number Received
                        print(f"[-] Signal received. Group Number: {group_number}")

                        # 2. Construct API URL
                        # Format: {base_url}/led/group/{group_number}/toggle
                        api_endpoint = f"{API_BASE_URL}/led/group/{group_number}/toggle"
                        
                        # Feedback: Endpoint being called
                        print(f"    Target Endpoint: {api_endpoint}")

                        # 3. Send HTTP Request
                        try:
                            response = requests.get(api_endpoint, timeout=5)
                            
                            # Feedback: API Response
                            if response.status_code == 200:
                                print(f"    [SUCCESS] Server responded: {response.status_code} OK")
                            else:
                                print(f"    [WARNING] Server responded: {response.status_code}")
                                print(f"    Message: {response.text}")
                                
                        except requests.exceptions.RequestException as e:
                            print(f"    [ERROR] Failed to reach API server: {e}")
                            
                        print("-" * 40) # Separator for readability

            except serial.SerialException as e:
                print(f"[ERROR] Serial communication lost: {e}")
                break # Exit loop or add reconnection logic here
                
    except serial.SerialException as e:
        print(f"[FATAL] Could not open serial port {SERIAL_PORT}.")
        print(f"Error: {e}")
        print("Check if the Arduino is connected and the port name is correct.")
        
    except KeyboardInterrupt:
        print("\n[STOP] Program terminated by user.")
        
    finally:
        if ser and ser.is_open:
            ser.close()
            print("Serial connection closed.")

if __name__ == "__main__":
    main()