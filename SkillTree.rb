def solution(skill, skill_trees)
    answer = 0

    #먼저 map 만듦
    map = {}
    skill.split('').each_with_index do |item, index|
        map[item] = index
    end

    skill_trees.each do |elem|
        stack = []
        elem.split('').each_with_index do |t,i|
            if map[t]
                if stack.length == 0 || stack[stack.length-1] +1 == map[t]
                    if stack.length == 0 && map[t] != 0
                        break
                    end
                    stack.push(map[t])
                else
                    break
                end
            end

            if i == elem.length-1
                answer += 1
            end
        end
    end

    return answer
end
