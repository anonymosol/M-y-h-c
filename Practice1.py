import os
print(os.listdir('spambase'))

import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.naive_bayes import MultinomialNB
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score

# Load the Spambase dataset
data = pd.read_csv('spambase/spambase.csv')  # Update to reflect the subfolder path  # Replace with actual filename if different

# Separate features and labels
X = data.drop(columns=['label_column_name'])  # Replace 'label_column_name' with the actual name of the label column
y = data['label_column_name']  # Use the actual name of the label column for spam/not spam

# Train-test split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Model Training
lr_model = LogisticRegression()
lr_model.fit(X_train, y_train)

nb_model = MultinomialNB()
nb_model.fit(X_train, y_train)

# Model Evaluation
lr_preds = lr_model.predict(X_test)
nb_preds = nb_model.predict(X_test)

print("Logistic Regression Performance:")
print("Accuracy:", accuracy_score(y_test, lr_preds))
print("Precision:", precision_score(y_test, lr_preds))
print("Recall:", recall_score(y_test, lr_preds))
print("F1 Score:", f1_score(y_test, lr_preds))

print("\nNaive Bayes Performance:")
print("Accuracy:", accuracy_score(y_test, nb_preds))
print("Precision:", precision_score(y_test, nb_preds))
print("Recall:", recall_score(y_test, nb_preds))
print("F1 Score:", f1_score(y_test, nb_preds))
