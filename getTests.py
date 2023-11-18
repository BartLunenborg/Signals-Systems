import os
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options
import getpass
import time
import sys


def download_files(base_link, username, password, in_file_count, out_file_count, script_directory):
    # Set up Chrome options
    chrome_options = Options()
    chrome_options.add_argument("--headless")  # You can remove this line to see the browser

    # Set download directory to the script directory
    prefs = {"download.default_directory": script_directory}
    chrome_options.add_experimental_option("prefs", prefs)

    # Start the browser
    driver = webdriver.Chrome(options=chrome_options)

    # Navigate to the login page
    driver.get("https://themis.housing.rug.nl/log/in")

    # Fill out the login form
    username_field = driver.find_element("name", "user")
    password_field = driver.find_element("name", "password")
    username_field.send_keys(username)
    password_field.send_keys(password)
    password_field.send_keys(Keys.RETURN)

    # Wait for the login to complete
    time.sleep(2)

    # Download the files
    for i in range(1, in_file_count + 1):
        in_link = f"{base_link}{i}.in"
        driver.get(in_link)
        time.sleep(1)  # Adjust the sleep duration based on your needs
        content = driver.find_element("tag name", "pre").text + "\n"
        save_path = os.path.join(script_directory, f"{i}.in")
        with open(save_path, "w") as file:
            file.write(content)

    for i in range(1, out_file_count + 1):
        out_link = f"{base_link}{i}.out"
        driver.get(out_link)
        time.sleep(1)  # Adjust the sleep duration based on your needs
        content = driver.find_element("tag name", "pre").text + "\n"
        save_path = os.path.join(script_directory, f"{i}.out")
        with open(save_path, "w") as file:
            file.write(content)

    # Close the browser
    driver.quit()


if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python script.py base_link in_file_count out_file_count")
        sys.exit(1)

    # Your username
    username = "s3410579"

    base_link = sys.argv[1]
    in_file_count = int(sys.argv[2])
    out_file_count = int(sys.argv[3])

    # Get the directory of the script
    script_directory = os.path.dirname(os.path.abspath(__file__))

    # Prompt for the password
    password = getpass.getpass(f"Please type the password for {username}: ")

    download_files(base_link, username, password, in_file_count, out_file_count, script_directory)
