#!/usr/bin/python
import random

class Encrypt:
	def __init__(self):
		self.code=[chr(i) for i in range(97,123)]
		print("alph: "+"".join(self.code))
		random.shuffle(self.code)
		self.alph=[chr(i) for i in range(97,123)]

	def __str__(self):
		return "code: "+"".join(self.code)

	def setCode(self,data):
		self.code=list(data)

	def getCode(self):
		return "".join(self.code)

	def toEncode(self, s):
#		return "toEncode"
		result=""
		for i in s:
			if i in self.code:
				j=self.alph.index(i)
				print(j)
				result+=self.code[j]
			else:
				result+=i

		return result

	def toDecode(self, s):
#		return "toDecode"
		result=""
		for i in s:
			if i in self.code:
				j=self.code.index(i)
				result+=self.alph[j]
			else:
				result+=i

		return result

if __name__=='__main__':
	e=Encrypt()
	print(e)
	s1="there is NO spoon"
	print("input: "+s1)
	s2=e.toEncode(s1)
	print("encode: "+s2)
	s3=e.toDecode(s2)
	print("decode: "+s3)

