################################ Covid Vaccine availability notifier ###############################
# Author - Vivek Bhageria
# Posted on - https://nerdyelectronics.com
# ##################################################################################################

import requests   # to send GET requests to the server
import boto3      # for communication with AWS and send emails
from botocore.exceptions import ClientError   # AWS communication errors
from datetime import date  # to create the date string
import json   #to parse the json response from server

####################################################################################################
# Function Name - checkStatus()									                                   #
# Arguments - None										                                           #
# Return type - String										                                       #
# Return - string with information of centers where vaccine is available			               #
####################################################################################################
def checkStatus():
    today = date.today() #get today's date from system
    target_date = str(today.day) + "-" + str(today.month) +"-" + str(today.year)
    payload = {'district_id':'8','date':target_date}	#payload with district ID and date
    
    headers={'user-agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/90.0.4430.93 Safari/537.36'}
    byDistrict_URL = "https://cdn-api.co-vin.in/api/v2/appointment/sessions/public/calendarByDistrict"
    
    data = requests.get(byDistrict_URL,headers=headers,params = payload) # Send a GET request with the defined payload
    json_data=  data.json()
    message = ''

###Loop through the data###
    for i in range(len(json_data['centers'])): #loop for all centers
        center = 'center : ' + (json_data['centers'][i]['name']) + '<br />' + "District : " + json_data['centers'][i]['district_name'] + '<br />'+ 'address : ' + (json_data['centers'][i]['address'])

        for j in range(len(json_data['centers'][i]['sessions'])):  #loop for all sessions in a center
            capacity = json_data['centers'][i]['sessions'][j]['available_capacity'] #available capacity
            minAge = json_data['centers'][i]['sessions'][j]['min_age_limit']  #minimum age limit for vaccination in this center session


            if(capacity>0 and minAge == 18):  #add to message only if capacity is more than zero
                available_date = json_data['centers'][i]['sessions'][j]['date']
                message = message + center + "<br />"  + "Date : " + available_date + "<br />" + "Available Capacity : " + str(capacity) + "<br />" + "Minimum Age : " + str(minAge) + "<br /><br />"
    return(message)
################################### End of Funtion checkStatus() ###################################

####################################################################################################
# Function Name - notify(string,string)								                               #
# Arguments - two arguments                                                                        #
#     1. message - The body of the email                                                           #
#     2. RECIPIENT - The recipient email ID							                               #
# Return type - None										                                       #
####################################################################################################
def notify(message, RECIPIENT):
    CHARSET = "UTF-8"
    SUBJECT = "Vaccine available!!"
    # Create a new SES resource and specify a region.
    client = boto3.client('ses',region_name=AWS_REGION)

    # Try to send the email.
    try:
        #Provide the contents of the email.
        response = client.send_email(
            Destination={
                'ToAddresses': [
                    RECIPIENT,
                ],
            },
            Message={
                'Body': {
                    'Html': {
                        'Charset': CHARSET,
                        'Data': message,
                    },
                    'Text': {
                        'Charset': CHARSET,
                        'Data': message,
                    },
                },
                'Subject': {
                    'Charset': CHARSET,
                    'Data': SUBJECT,
                },
            },
            Source=SENDER,
        )
    # Display an error if something goes wrong.	
    except ClientError as e:
        print(e.response['Error']['Message'])
    else:
        print("Email sent! Message ID:"),
        print(response['MessageId'])

##################################### End of Function notify() #####################################
		
		
RECIPIENT = "vixxxxxxxxxxxxx@gmail.com" # receivers email ID. Can be same as sender 
SENDER = "vixxxxxxxxxxxxx@gmail.com" # sender email ID 
AWS_REGION = "ap-south-1" #Region where the SES email ID is verified. For me it was Mumbai, hence "ap-south-1" 

BODY_TEXT = ((checkStatus())) # here we ping the server and get the status. The status is then stored in BODY_TEXT  
if(BODY_TEXT != ''): # if BODY_TEXT is not empty means that there are some slots available. Notify only in that case 
    notify(BODY_TEXT,RECIPIENT) # if slots available, notify