# smart-safe-with-microcontroller

This project uses an ATMEGA32 microcontroller which allows its user to open or lock this safe with a password.

Firstly, it ask the user to set a password and it stores it in EEPROM which mean it won't be deleted after removing power from the safe.

![Screenshot 2023-02-27 222820](https://user-images.githubusercontent.com/119271600/221718113-27566929-876e-4af4-ba0c-64d31242ef11.png)

After setting a password for the first time, it will regularly ask the user to enter the password every time the user want to open the safe.

![Screenshot 2023-02-27 222943](https://user-images.githubusercontent.com/119271600/221718333-5ecc23e4-79af-4016-9c76-bf6cae7d5861.png)

If the entered password is correct the safe will open easly.

![Screenshot 2023-02-27 225054](https://user-images.githubusercontent.com/119271600/221718456-f7219a89-0323-47f6-9c8d-0d9e6982a1ef.png)

Other wise, it will only let the user to get 2 tries until it shuts down all systems.

![Screenshot 2023-02-27 225125](https://user-images.githubusercontent.com/119271600/221718790-2be648cb-266a-4025-8ece-40a206fd6ec9.png)

This microcontroller is programmed in C language using Atmel studio IDE and the code is in the files.
