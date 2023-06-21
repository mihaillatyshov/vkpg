import unittest

import requests

import time
 
host = "http://localhost:8080/api"

class TestThread(unittest.TestCase):
    def threadCreate(self, slug, json, resStatus = 201):
        with self.subTest(json=json, resStatus=resStatus):
            resp = requests.post(f"{host}/forum/{slug}/create", json=json)
            print(resp.status_code, ":   ", resp.json())
            self.assertEqual(resp.status_code, resStatus)
        

    def test_threadCreate(self):
        print()
        self.threadCreate(f"forum-slug-1", {
            "title": f"Title 1",
            "author": f"lm1",
            "message": "Some message 1"
        })
        time.sleep(0.1)
        
        self.threadCreate(f"forum-slug-2", {
            "title": f"Title 2",
            "author": f"lm1",
            "message": "Some message 2",
            "created": "2017-01-01T00:00:00.000Z"
        })
        time.sleep(0.1)
            
        self.threadCreate(f"forum-slug-1", {
            "title": f"Title 2",
            "author": f"lm4",
            "slug": f"forum-slug-4",
            "message": "Some message 2"
        }, 409)

        self.threadCreate(f"forum-slug-3", {
            "title": f"Title 2",
            "author": f"lm1222",
            "message": "Some message 3"
            
        }, 404)
        
        self.threadCreate(f"forum-slug-331", {
            "title": f"Title 2",
            "author": f"lm1",
            "message": "Some message 3"
            
        }, 404)
        
        