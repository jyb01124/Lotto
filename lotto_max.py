from bs4 import BeautifulSoup
import requests, string

URL = "http://www.nlotto.co.kr/gameResult.do?method=byWin&drwNo="

html = requests.get(URL)
html = html.content
soup = BeautifulSoup(html,'html.parser')

num_par = soup.find_all("meta", id = "desc")
tmp = str(num_par[0]).split("회")
tmp_2 = str(tmp[0]).split(" ")
max_num = str(tmp_2[2])

f = open('max_num.w','w')
f.write(max_num)
f.close()