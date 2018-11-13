Group No.1 : Nobike by ปลากระป๋อง <br/>
<h4>สมาชิกประกอบด้วย</h4>
นายคุณานนต์ บุรเทพ 5910500121 <br/>
นายชาญชัย ชนาเทพาพร 5910503707 <br/>
ชั้นปีที่ 2 ปีการศึกษา 2560 คณะ วิศวกรรมศาสตร์ ภาควิชาคอมพิวเตอร์ มหาวิทยาลัย เกษตรศาสตร์ บางเขน <br/>

ไฟล์ : nobike_website.rar <br/>
เก็บโค้ดในการทำ mobile app ทั้งหมด โดยเริ่มต้นที่ไฟล์ index.html โดยใส่ลงใน www folder ของ <br/>
web server ที่รองรับระบบ php <br/>
 
โฟลเดอร์ : practicum_board_input <br/>
เก็บโค้ดสำหรับการควบคุมการส่งค่าจาก GPS ไปหา  Wifi เพื่ออัพขึ้น server <br/>
ภายในไฟล์ practicum_board_1 ประกอบไปด้วย 2 โฟลเดอร์หลักๆ <br/>
ไฟล์โค้ด gps_to_esp : เป็นโค้ดสำหรับรับค่าและแปลงค่าของ GPS บนบอร์ด practicum และ ส่งค่าที่รับมาได้จาก GPS ไปยัง WiFi module <br/>
ไฟล์โค้ด esp_to_server : เป็น โค้ดสำหรับการส่งค่าของ WiFi module ไปยัง Web Server <br/>

โฟลเดอร์ : practicum_board_output <br/>
เก็บโค้ดสำหรับการควบคุมไฟ บัสเซอร์ และ รับคำสั่งเปิด/ปิดจาก server <br/>
ไฟล์โค้ด practicum_nobike.c : เป็นโค้ด set การเปิด/ปิด ไฟและบัสเซอร์ <br/>
ไฟล์โค้ด esp8266_module.ino : เป็นโค้ดในการรับคำสั่งจาก server <br/>


<h4>อุปกรณ์ที่ใช้</h4><br/>
Practicum Board 2 ชิ้น <br/>
GPS Module neo6mv2 1 ชิ้น <br/>
ESP WiFi Module 2 ชิ้น <br/>
Bi-directional Logic Level Converter 3V to 5V 2 ชิ้น <br/>
AMS1117 3.3V Power Supply Module (Voltage Regulator 3.3 V) 2 ชิ้น <br/>
LED 2 หลอด <br/>
Buzzer 1 ชิ้น <br/>
ตัวต้านทาน(ขนาด) 3 ตัว <br/>

<h4>ไลบรารีที่ใช้ </h4><br/>
ESP8266WiFi.h <br/>

Link สำหรับการเลือก Board เป็น WiFi module ใน Arduino ide <br/>
http://arduino.esp8266.com/stable/package_esp8266com_index.json <br/>

SoftwareSerial.h <br/>
