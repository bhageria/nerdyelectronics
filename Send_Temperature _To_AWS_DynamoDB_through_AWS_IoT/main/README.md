# IoT Project to read Temperature. Send Temperature to AWS IoT and store in AWS DynamoDB

Tutorial by https://nerdyelectronics.com:

## Block Diagram:  

![alt text](https://github.com/bhageria/nerdyelectronics/blob/master/Send_Temperature%20_To_AWS_DynamoDB_through_AWS_IoT/images/read_temperature%20in%20AWS%20DynamoDB%20block-diagram.jpg)

## Circuit Diagram:  

![alt text](https://github.com/bhageria/nerdyelectronics/blob/master/Send_Temperature%20_To_AWS_DynamoDB_through_AWS_IoT/images/aws_iot_temperature_circuit.jpg)

## Detailed instructions:  
   https://nerdyelectronics.com/iot/read-temperature-and-send-to-cloud-dynamodb-iot-project/

## Explanation and instructions video:  
   https://www.youtube.com/watch?v=lA_iBwDZxsw

## How to connect NodeMCU to AWS IoT  
   https://nerdyelectronics.com/iot/nodemcu-to-aws-iot-service/
   
1)  [AWS IoT - Create a Thing](https://nerdyelectronics.com/iot/how-to-create-a-thing-in-aws-iot/)
2)  [Convert Certificates from .pem to .der format](https://nerdyelectronics.com/iot/how-to-convert-certificates-from-pem-to-der-format/)
3)  [Connect NodeMCU to AWS IoT Core](https://nerdyelectronics.com/iot/how-to-connect-nodemcu-to-aws-iot-core/)

## Time keeping in IoT projects using NTP  
   https://nerdyelectronics.com/iot/esp8266/getting-time-from-internet-using-esp8266-ntp/

Do make sure to update the following lines:

1. `const char* ssid = "XXXXXXXXX";` - Add your Wifi Name here
2. `const char* password = "XXXXXXXXXXXXXx";`  Add your Wifi password here
3. `const char* AWS_endpoint = "XXXXXXXXXXX-ats.iot.us-east-2.amazonaws.com";` Add your AWS Endpoint here.
