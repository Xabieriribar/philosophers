import sys
import re

LINE_RE = re.compile(r"^\s*(\d+)\s+(\d+)\s+(.+?)\s*$")

def left_neighbor(pid, n):
    return n if pid == 1 else pid - 1

def right_neighbor(pid, n):
    return 1 if pid == n else pid + 1

def main():
    if len(sys.argv) != 3:
        print("Usage: python3 check_philo_log.py <log_file> <number_of_philosophers>")
        sys.exit(1)

    log_file = sys.argv[1]
    try:
        n = int(sys.argv[2])
    except ValueError:
        print("Error: number_of_philosophers must be an integer")
        sys.exit(1)

    # Estado por filósofo
    forks_taken = {i: 0 for i in range(1, n + 1)}
    eating = set()

    errors = []
    max_eating = 0
    max_eating_timestamp = None

    with open(log_file, "r", encoding="utf-8") as f:
        for line_no, raw_line in enumerate(f, start=1):
            line = raw_line.rstrip("\n")
            if not line.strip():
                continue

            match = LINE_RE.match(line)
            if not match:
                errors.append(f"[line {line_no}] Invalid format: {line}")
                continue

            timestamp = int(match.group(1))
            pid = int(match.group(2))
            action = match.group(3)

            if pid < 1 or pid > n:
                errors.append(f"[line {line_no}] Invalid philosopher id {pid}: {line}")
                continue

            if action == "has taken a fork":
                forks_taken[pid] += 1
                if forks_taken[pid] > 2:
                    errors.append(
                        f"[line {line_no}] Philosopher {pid} took more than 2 forks before eating: {line}"
                    )

            elif action == "is eating":
                if forks_taken[pid] != 2:
                    errors.append(
                        f"[line {line_no}] Philosopher {pid} started eating with {forks_taken[pid]} forks: {line}"
                    )

                l = left_neighbor(pid, n)
                r = right_neighbor(pid, n)

                if l in eating or r in eating:
                    errors.append(
                        f"[line {line_no}] Neighbor conflict: philosopher {pid} is eating while "
                        f"neighbor {l if l in eating else r} is already eating: {line}"
                    )

                eating.add(pid)
                if len(eating) > max_eating:
                    max_eating = len(eating)
                    max_eating_timestamp = timestamp

            elif action == "is sleeping":
                if pid in eating:
                    eating.remove(pid)
                forks_taken[pid] = 0

            elif action == "is thinking":
                # pensar no cambia el estado de forks directamente
                pass

            elif action == "died":
                # no hacemos nada especial, solo lo registramos como válido
                pass

            else:
                errors.append(f"[line {line_no}] Unknown action: {line}")

    print("==== PHILO LOG CHECK ====")
    print(f"Philosophers: {n}")
    print(f"Max simultaneous eaters: {max_eating}", end="")
    if max_eating_timestamp is not None:
        print(f" at timestamp {max_eating_timestamp}")
    else:
        print()

    theoretical_max = n // 2
    print(f"Theoretical maximum simultaneous eaters: {theoretical_max}")
    if max_eating > theoretical_max:
        print("ERROR: More philosophers ate simultaneously than physically possible.")

    print()

    if errors:
        print(f"Found {len(errors)} issue(s):")
        for err in errors:
            print(err)
    else:
        print("No structural issues found in the log.")

if __name__ == "__main__":
    main()