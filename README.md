# Anggota Kelompok 12
1. M Dupan Desradha E (14117118)
2. Muhammad Izzul Islam (14117023)
3. Nazel Marfi Alfawwaz (14116012)
4. Ahmad Rosyid Al Khairi (14116062)

Laporan Project dapat dilihat disini [Overleaf](https://www.overleaf.com/read/sppdbrzydzcq)


# JemOto
JemOto (Jemuran Otomatis) merupakan prototype sebagai tugas besar untuk memenuhi matakuliah sistem tertanam, program studi Teknik Informatika, Institut Teknologi Sumatera T.A. 2021. JemOto sendiri berfungsi sebagai jemuran otomatis dan dapat dikendalikan dengan menggunakan telegram bot.
Penggunaan NodeMCU esp8266 v3 dalam pengembangannya untuk memungkinkan pemanfaatan Internet of Things agar dapat lebih memudahkan dalam kendali serta monitoring. <br />
Adapun sensor-sensor dan tambahan yang digunakan sebagai berikut.
1. DHT11
2. LDR Module 
3. Raindrop Sensor 
4. Micro Servo SG90 
5. Passive Buzzer 
6. Telegram Bot dari botfather

# Arsitektur Sistem
![Arsitektur sistem](https://user-images.githubusercontent.com/49479754/147742630-15934219-bbf9-4c42-926f-72a93750bf8d.png)

Pada gambar Arsitektur Sistem terdapat beberapa komponen yang telah dikelompokkan. 
1. Pertama ada NodeMCU Esp8266 sebagai inti dari sistem ini. 
2. Kedua adalah input, komponen pada input terdiri dari dht11 merupakan sensor tambahan untuk mengecek suhu sekitar, ldr module untuk mengecek intensitas cahaya, dan raindrop sensor modul untuk mengecek cuaca. Ketiga sensor ini akan bekerja secara waktu nyata dan akan mengirimkan data yang telah ditangkap dan selanjutnya akan dikirim ke NodeMCU agar dapat diolah.
3. Ketiga ada output, pada output ini terdapat 2 aktuator yang akan bekerja sesuai apa yang telah diperintahkan oleh NodeMCU. ada micro servo sg90 sebagai penggerak untuk memasukkan dan mengeluarkan jemuran dan passive buzzer sebagai suara tanda peringatan. 
4. Dan yang terakhir ada media komunikasi, media komunikasi yang digunakan adalah telegram, penggunaan bot pada telegram akan memudahkan memonitoring dan mengendalikan JemOto

# Video Demo Project
[![Video Demo Project](https://img.youtube.com/vi/a9QlhMGlclo/0.jpg)](https://www.youtube.com/watch?v=a9QlhMGlclo) </br>

Alternatif link video demo project : https://www.youtube.com/embed/a9QlhMGlclo

# Referensi
[1] Muhammad Robith Adani, “Mengenal Apa Itu Internet of Things dan Contoh Penerapannya,” Sekawan Media. p. 1, 2020, [Online]. Available: https://www.sekawanmedia.co.id/pengertian-internet-of-things/. <br />
[2] S. Wasista, Setiawardhana, D. A. Saraswati, and E. Susanto, Aplikasi Internet of Things (IoT) dengan ARDUINO dan ANDROID. Yogyakarta: CV BUDI UTAMA, 2019. <br />
[3] M. V. Overbeek, “Internet of Things (IoT) dalam Bidang Informatika,” Universitas Multimedia Nusantara. [Online]. Available: https://www.umn.ac.id/internet-things-iot-dalam-bidang-informatika/. <br />
[4] R. L. Kahimpong, M. Umboh, and B. Maluegha, “Rancang Bangun Prototipe Penjemur Pakaian Otomatis Berbasis Mikrokontroler Arduino Uno,” Ubiquitous Comput. its Appl. J., vol. 6, pp. 41–54, 2018, doi: 10.51804/ucaiaj.v1i1.41-54
