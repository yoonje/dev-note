from collections import deque


def dfs(board, start_node, goal_node):
    # 방문 여부를 카운팅 할 배열
    visited = [[0 for _ in range(len(board[0]))] for _ in range(len(board))]

    need_visit = deque()

    # 초기화
    need_visit.append(start_node)
    visited[start_node[0]][start_node[1]] = 1

    while need_visit:

        row, col = need_visit.pop()

        if [row, col] == goal_node:
            return True

        if row > 0:
            if visited[row - 1][col] == 0 and board[row - 1][col] == 0:
                need_visit.append([row - 1, col])
                visited[row - 1][col] = 1

        if col > 0:
            if visited[row][col - 1] == 0 and board[row][col - 1] == 0:
                need_visit.append([row, col - 1])
                visited[row][col - 1] = 1

        if row < len(board) - 1:
            if visited[row + 1][col] == 0 and board[row + 1][col] == 0:
                need_visit.append([row + 1, col])
                visited[row + 1][col] = 1

        if col < len(board[0]) - 1:
            if visited[row][col + 1] == 0 and board[row][col + 1] == 0:
                need_visit.append([row, col + 1])
                visited[row][col + 1] = 1

    return False


if __name__ == "__main__":
    board = [
        [0, 0, 0, 0, 1, 1],
        [1, 0, 1, 0, 1, 1],
        [1, 0, 1, 0, 0, 1],
        [1, 0, 1, 1, 0, 0],
        [1, 0, 1, 1, 0, 0],
        [1, 0, 0, 0, 0, 1],
        [1, 0, 1, 1, 1, 1],
        [1, 0, 0, 0, 0, 0],
    ]
    start_node = [0, 0]
    goal_node = [5, 4]
    # dfs 통해 시작 노드에서 도착 노드까지의 탐색 가능한지 리턴
    print(dfs(board, start_node, goal_node))
