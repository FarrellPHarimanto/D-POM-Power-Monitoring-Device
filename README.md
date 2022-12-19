# D-POM-Power-Monitoring-Device

Background:
1. The general liability of humans is forgetfulness, sometimes they leave electronic devices without turning them off,
2. Electricity prices continue to increase in Indonesia and electricity use per capita also continues to increase according to the Indonesian Central Statistics Agency (Badan Pusat Statistik Indonesia),
3. Able to prepare electronic devices online when needed to be more time efficient.

Purpose:
1. Reducing the use of energy.
2. Making it easier to control electronic devices via the Internet.
3. Monitor the use of electricity in electronic devices.
4. Improving energy efficiency in various sectors.

Hardware Components:
1. SONOFF POW (Power Measuring wifi switch):
   - Microcontroller : ESP8266
   - Single Phase Energy Monitor Chip : HLW8012
   - Relay

Protocol:
Our data protocol uses HTTP for efficient data transmission. It is because HTTP can deliver data in various formats and sizes. HTTP is also arguably simpler than most protocol, due to that, the development can be significantly swift. HTTP also has advantage whereas it only keeps connection alive while a device sends and receives data, in other words, it is more energy efficient compared to other protocols that upholds the connection all the time.
