import requests

host = "http://localhost:8080/api"

for i in range(5):
    resp = requests.post(host + "/user/lm" + str(i) + "/create", json = {
        "email": "lmail" + str(i) + "@mail.ru",
        "about": "some about " + str(i),
        "fullname": "Name " + str(i)
    })
    
    print(resp.status_code)