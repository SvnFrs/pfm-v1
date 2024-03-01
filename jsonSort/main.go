package main

import (
	"encoding/json"
	"fmt"
	"os"
	"sort"
)

type ExpenseData map[string]map[string]map[string]interface{}

func main() {
	// read the JSON data from the file
	file, err := os.ReadFile("../data/Expenses.json")
	if err != nil {
		// fmt.Println("Error reading file:", err)
		return
	}

	// rarse the JSON data into ExpenseData struct
	var expenses ExpenseData
	err = json.Unmarshal(file, &expenses)
	if err != nil {
		// fmt.Println("Error parsing JSON:", err)
		return
	}

	// sort the years in ascending order
	years := make([]string, 0, len(expenses))
	for year := range expenses {
		years = append(years, year)
	}
	sort.Strings(years)

	// create a new sorted ExpenseData
	sortedExpenses := make(ExpenseData)
	for _, year := range years {
		sortedExpenses[year] = expenses[year]
	}

	// convert the sorted ExpenseData back to JSON
	sortedJSON, err := json.MarshalIndent(sortedExpenses, "", "\t")
	if err != nil {
		// fmt.Println("Error converting to JSON:", err)
		return
	}

	// ưrite the sorted JSON to a new file
	err = os.WriteFile("../data/Cache.json", sortedJSON, os.ModePerm)
	if err != nil {
		// fmt.Println("Error writing file:", err)
		return
	}

	fmt.Println("Sorting completed. Sorted data is stored in 'data/Cache.json'.")
}
