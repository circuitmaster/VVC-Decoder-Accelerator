#!/usr/bin/env bash
# test.sh - sweep parameters and capture timing to CSV.

XCLBIN="vvc_decoder_new.xclbin"
BLOCK_SIZES=(2 4 8 16 32 64)
SIZES=(1 10 100 1000 10000 100000)
RUNS=10
total_runs=$(( ${#BLOCK_SIZES[@]} * ${#SIZES[@]} * RUNS ))
run_idx=0
show_progress() {
    run_idx=$((run_idx + 1))
    printf "\r[%d/%d] bs=%s sz=%s" "$run_idx" "$total_runs" "$bs" "$sz"
}
trap '[[ $BASH_COMMAND == *"./main "* ]] && show_progress' DEBUG
calc_stats() {
    local values=("$@")
    # Outputs mean, median, variance as comma-separated floats.
    printf "%s\n" "${values[@]}" | sort -n | awk '
        { a[NR]=$1; sum+=$1 }
        END {
            n=NR; mean=sum/n
            if (n % 2) median=a[(n+1)/2]
            else median=(a[n/2]+a[n/2+1])/2
            for(i=1;i<=n;i++){ diff=a[i]-mean; var+=diff*diff }
            var/=n
            printf "%.6f,%.6f,%.6f", mean, median, var
        }
    '
}
SHIFT=5
OUTPUT_MIN=0
OUTPUT_MAX=10000
CSV_OUT="timings.csv"

echo "block_size,size,total_mean,total_median,total_variance,input_mean,input_median,input_variance,kernel_mean,kernel_median,kernel_variance,output_mean,output_median,output_variance" > "${CSV_OUT}"

for bs in "${BLOCK_SIZES[@]}"; do
    for sz in "${SIZES[@]}"; do
        total_vals=()
        input_vals=()
        kernel_vals=()
        output_vals=()

        for ((run=1; run<=RUNS; run++)); do
            OUTPUT=$(./main "${XCLBIN}" "${bs}" "${sz}" "${SHIFT}" "${OUTPUT_MIN}" "${OUTPUT_MAX}")

            total=$(echo "${OUTPUT}" | awk -F': ' '/Total execution time/ {print $2}' | awk '{print $1}')
            input=$(echo "${OUTPUT}" | awk -F': ' '/Input data transfer time/ {print $2}' | awk '{print $1}')
            kernel=$(echo "${OUTPUT}" | awk -F': ' '/Kernel execution time/ {print $2}' | awk '{print $1}')
            output=$(echo "${OUTPUT}" | awk -F': ' '/Output data transfer time/ {print $2}' | awk '{print $1}')

            total_vals+=("${total}")
            input_vals+=("${input}")
            kernel_vals+=("${kernel}")
            output_vals+=("${output}")
        done

        total_stats=$(calc_stats "${total_vals[@]}")
        input_stats=$(calc_stats "${input_vals[@]}")
        kernel_stats=$(calc_stats "${kernel_vals[@]}")
        output_stats=$(calc_stats "${output_vals[@]}")

        echo "${bs},${sz},${total_stats},${input_stats},${kernel_stats},${output_stats}" >> "${CSV_OUT}"
    done
done

echo "Results written to ${CSV_OUT}"