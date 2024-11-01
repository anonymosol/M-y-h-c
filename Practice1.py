# Import necessary libraries
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.naive_bayes import MultinomialNB
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score
import os

# Check current directory and verify file path if needed
print("Current Directory:", os.getcwd())

# Load the Spambase dataset - Update path as needed if it's not in the current directory
data = pd.read_csv('spambase\spambase.csv')  # Replace with your exact path

# Inspect data to understand structure and confirm the label column
print(data.head())
print(data.columns)  # Check column names to confirm which one is the target (label) column

# Define the label column name based on your dataset structure
# Typically, for the Spambase dataset, the last column represents the label (1 for spam, 0 for not spam)
label_column = data.columns[-1]  # Adjust if needed based on your file's structure

# Separate features and target variable
X = data.drop(columns=[label_column])  # All columns except the label column are features
y = data[label_column]  # The label column as the target variable

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Initialize models
lr_model = LogisticRegression(max_iter=1000)  # Increase max_iter if needed for convergence
nb_model = MultinomialNB()

# Train the Logistic Regression model
lr_model.fit(X_train, y_train)

# Train the Naive Bayes model
nb_model.fit(X_train, y_train)

# Make predictions with both models
lr_preds = lr_model.predict(X_test)
nb_preds = nb_model.predict(X_test)

# Evaluate Logistic Regression model
print("\nLogistic Regression Performance:")
print("Accuracy:", accuracy_score(y_test, lr_preds))
print("Precision:", precision_score(y_test, lr_preds))
print("Recall:", recall_score(y_test, lr_preds))
print("F1 Score:", f1_score(y_test, lr_preds))

# Evaluate Naive Bayes model
print("\nNaive Bayes Performance:")
print("Accuracy:", accuracy_score(y_test, nb_preds))
print("Precision:", precision_score(y_test, nb_preds))
print("Recall:", recall_score(y_test, nb_preds))
print("F1 Score:", f1_score(y_test, nb_preds))

# Save the Logistic Regression model as a file for deployment if needed
import joblib
joblib.dump(lr_model, 'spam_classifier_lr.pkl')

print("\nModel saved as 'spam_classifier_lr.pkl'.")
