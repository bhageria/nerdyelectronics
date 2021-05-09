import requests
import boto3
from botocore.exceptions import ClientError
from datetime import date
import json

####################################################################################################
# Function Name - checkStatus()                                                                    #
# Arguments - None                                                                                 #
# Return type - String                                                                             #
# Return - string with information of centers where vaccine is available                           #
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

###Loop through the data
    for i in range(len(json_data['centers'])):
        center = 'center : ' + (json_data['centers'][i]['name']) + '<br />' + "District : " + json_data['centers'][i]['district_name'] + '<br />'+ 'address : ' + (json_data['centers'][i]['address'])

        for j in range(len(json_data['centers'][i]['sessions'])):
            capacity = json_data['centers'][i]['sessions'][j]['available_capacity']
            minAge = json_data['centers'][i]['sessions'][j]['min_age_limit']


            if(capacity>=0 and minAge == 18):
                available_date = json_data['centers'][i]['sessions'][j]['date']
                message = message + center + "<br />"  + "Date : " + available_date + "<br />" + "Available Capacity : " + str(capacity) + "<br />" + "Minimum Age : " + str(minAge) + "<br /><br />"
    print(message)
    return(message)
################################### End of Funtion checkStatus() ###################################

####################################################################################################
# Function Name - notify(string,string)                                                            #
# Arguments - two arguments                                                                        #
#     1. message - The body of the email                                                           #
#     2. RECIPIENT - The recipient email ID                                                        #
# Return type - None                                                                               #
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
		
		
RECIPIENT = "vixxxxxxxxxxxxx@gmail.com"	#Add the Recipient Email ID here
SENDER = "vixxxxxxxxxxxxx@gmail.com"		#Add the Sender Email ID here
AWS_REGION = "ap-south-1"

BODY_TEXT = ((checkStatus()))

if(BODY_TEXT != ''):
    notify(BODY_TEXT,RECIPIENT)
