package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"os"
	"sort"
)

type ExpenseData map[string]map[string]map[string]interface{}

func main() {
	// Read the JSON data from the file
	file, err := ioutil.ReadFile("../testExpenses.json")
	if err != nil {
		fmt.Println("Error reading file:", err)
		return
	}

	// Parse the JSON data into ExpenseData struct
	var expenses ExpenseData
	err = json.Unmarshal(file, &expenses)
	if err != nil {
		fmt.Println("Error parsing JSON:", err)
		return
	}

	// Sort the years in ascending order
	years := make([]string, 0, len(expenses))
	for year := range expenses {
		years = append(years, year)
	}
	sort.Strings(years)

	// Create a new sorted ExpenseData
	sortedExpenses := make(ExpenseData)
	for _, year := range years {
		sortedExpenses[year] = expenses[year]
	}

	// Convert the sorted ExpenseData back to JSON
	sortedJSON, err := json.MarshalIndent(sortedExpenses, "", "\t")
	if err != nil {
		fmt.Println("Error converting to JSON:", err)
		return
	}

	// Write the sorted JSON to a new file
	err = ioutil.WriteFile("testCache.json", sortedJSON, os.ModePerm)
	if err != nil {
		fmt.Println("Error writing file:", err)
		return
	}

	fmt.Println("Sorting completed. Sorted data is stored in 'testCache.json'.")
}