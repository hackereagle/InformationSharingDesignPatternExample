from __future__ import annotations
from typing import List

class Contex():
	def __init__(self, strategy: ISortStrategy):
		self._strategy = strategy
	
	def SetStrategy(self, strategy: ISortStrategy):
		self._strategy = strategy
	
	def DoSomething(self, dataset: List):
		print("Do something before sorting, list: ", dataset)
		self._strategy.Sort(dataset)
		print("After doing something and list: ", dataset)

class ISortStrategy():
	def Sort(self, dataset: List) -> List:
		pass

class SortAcsending(ISortStrategy):
	def Sort(self, dataset: List) -> List:
		print("In SortAcsending")
		dataset.sort()
		return dataset

class SortDescending(ISortStrategy):
	def Sort(self, dataset: List) -> List:
		print("In SortDescending")
		dataset.sort()
		dataset.reverse()
		return dataset


if __name__ == "__main__":
	dataset = [1, 5, 4, 3, 2, 8]
	context = Contex(SortAcsending())
	context.DoSomething(dataset)

	print("\n======")
	context.SetStrategy(SortDescending())
	context.DoSomething(dataset)