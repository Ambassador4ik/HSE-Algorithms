import pandas as pd
import matplotlib.pyplot as plt
import os

# Get the absolute path to the directory where the current file is located
current_file_directory = os.path.dirname(os.path.abspath(__file__))

# Set the current working directory to the directory of the current file
os.chdir(current_file_directory)

# Initialize DataFrame to store concatenated results
all_results = pd.DataFrame()

# Iterate through the files and concatenate the results
for n in range(1, 6):
    file_name = f'results{n}.csv'
    if os.path.isfile(file_name):
        df = pd.read_csv(file_name)
        all_results = pd.concat([all_results, df], ignore_index=True)

# Group by ArrayType, SortType, ArraySize, and N, then calculate the mean duration
grouped_results = all_results.groupby(['ArrayType', 'SortType', 'ArraySize', 'N'], as_index=False)['Duration(µs)'].mean()

# Separate grouped results for total average
total_avg_results = grouped_results.groupby(['SortType', 'ArraySize', 'N'], as_index=False)['Duration(µs)'].mean()

# Get unique ArrayTypes
array_types = grouped_results['ArrayType'].unique()

# Plot total average on a separate window
fig_total = plt.figure(figsize=(9, 5), dpi=600)
ax_total = fig_total.add_subplot(111)
for N in total_avg_results['N'].unique():
    for sort_type in ['MergeSort', 'HybridSort']:
        if sort_type == 'MergeSort' and N == -1:
            # Filter for MergeSort
            sort_df = total_avg_results[(total_avg_results['SortType'] == sort_type)]
        elif sort_type == 'HybridSort' and N != -1:
            # Filter for HybridSort with each N
            sort_df = total_avg_results[(total_avg_results['SortType'] == sort_type) & (total_avg_results['N'] == N)]
        else:
            continue
        ax_total.plot(sort_df['ArraySize'], sort_df['Duration(µs)'], label=f'{sort_type} N={N}')
ax_total.set_title('Total Average Sorting Duration by Array Size and Sort Type')
ax_total.set_xlabel('Array Size')
ax_total.set_ylabel('Duration (µs)')
ax_total.legend()

# Plot for each ArrayType on the remaining separate windows
for i, array_type in enumerate(array_types):
    fig_array_type = plt.figure(figsize=(9, 5), dpi=600)
    ax_array_type = fig_array_type.add_subplot(111)
    array_type_data = grouped_results[grouped_results['ArrayType'] == array_type]

    for N in array_type_data['N'].unique():
        for sort_type in ['MergeSort', 'HybridSort']:
            if sort_type == 'MergeSort' and N == -1:
                # Filter for MergeSort
                sort_df = array_type_data[(array_type_data['SortType'] == sort_type)]
            elif sort_type == 'HybridSort' and N != -1:
                # Filter for HybridSort with each N
                sort_df = array_type_data[(array_type_data['SortType'] == sort_type) & (array_type_data['N'] == N)]
            else:
                continue
            ax_array_type.plot(sort_df['ArraySize'], sort_df['Duration(µs)'], label=f'{sort_type} N={N}')
    ax_array_type.set_title(f'Average Sorting Duration by Array Size and Sort Type for {array_type} Arrays')
    ax_array_type.set_xlabel('Array Size')
    ax_array_type.set_ylabel('Duration (µs)')
    ax_array_type.legend()

plt.show()
