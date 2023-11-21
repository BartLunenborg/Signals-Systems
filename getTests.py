# Python script used to automate downloading tests from Themis
import os
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options
import getpass
import time
import sys


def download_files(base_link, username, password, in_count, out_count):
    chrome_options = Options()
    chrome_options.add_argument("--headless")  # Hide browser

    # Set download directory to the script directory
    script_directory = os.path.dirname(os.path.abspath(__file__))
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

    # Download the in files
    for i in range(1, in_count + 1):
        driver.get(f"{base_link}{i}.in")
        time.sleep(1)  # Adjust the sleep duration based on your needs
        content = driver.find_element("tag name", "pre").text + "\n"
        save_path = os.path.join(script_directory, f"{i}.in")
        with open(save_path, "w") as file:
            file.write(content)

    # Download the out files
    for i in range(1, out_count + 1):
        driver.get(f"{base_link}{i}.out")
        time.sleep(1)  # Adjust the sleep duration based on your needs
        content = driver.find_element("tag name", "pre").text + "\n"
        save_path = os.path.join(script_directory, f"{i}.out")
        with open(save_path, "w") as file:
            file.write(content)

    # Close the browser
    driver.quit()


if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python3 getTests.py base_link in_count out_count")
        sys.exit(1)

    username = "s3410579"  # Your Themis username

    # Link you get when clicking on test case, minus the n.in or n.out
    base_link = sys.argv[1]

    in_count = int(sys.argv[2])   # Number of in files
    out_count = int(sys.argv[3])  # Number of out files

    # Prompt for the password to Themis (not hard-coded for safety)
    password = getpass.getpass(f"Please type the password for {username}: ")
    download_files(base_link, username, password, in_count, out_count)
