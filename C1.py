h = int(input("Nhap so gio lam: "))  # Input for hours worked
base_rate = 23000  # Base hourly rate
i = 1  # Counter for overtime

def check_salary(h, base_rate):
    if h <= 40:
        # If hours worked are less than or equal to 40, no overtime
        salary = h * base_rate
        print("Employee salary: ", salary)
    else:
        # Calculate salary with overtime
        base_salary = 40 * base_rate  # Regular salary for 40 hours
        overtime_hours = h - 40  # Overtime hours worked
        overtime_salary = overtime_hours * base_rate * 1.5  # Overtime is paid at 1.5x rate
        total_salary = base_salary + overtime_salary  # Total salary
        print("Employee salary: ", total_salary)

# Call the function
check_salary(h, base_rate)
