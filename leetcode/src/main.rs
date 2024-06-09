use std::fs;

use serde::Deserialize;

#[derive(Deserialize, Debug)]
struct Question{
    #[serde(rename = "acRate")]
    ac_rate: f64,
    title: String,
    #[serde(rename = "titleSlug")]
    title_slug: String,
    #[serde(rename = "paidOnly")]
    paid_only: bool
}

#[derive(Deserialize, Debug)]
struct  ProblemSetQuestionList {
    questions: Vec<Question>
}

#[derive(Deserialize, Debug)]
struct Data {
    #[serde(rename = "problemsetQuestionList")]
    problem_set_question_list: ProblemSetQuestionList
}

#[derive(Deserialize, Debug)]
struct Input {
    data : Data
}

const AC_RATE_TH: f64 = 55.0;

fn main() {
    let raw = fs::read_to_string("problems.json").unwrap();
    let input: Input = serde_json::from_str(&raw).unwrap();
    let mut questions = input.data.problem_set_question_list.questions
        .into_iter()
        .filter(|q| !q.paid_only && q.ac_rate <= AC_RATE_TH)
        .collect::<Vec<Question>>();
    questions.sort_by(|a,b| b.ac_rate.total_cmp(&a.ac_rate));

    let mut md_table: String = "| Solved | Title |\n|--------|-------|\n".into();

    for q in questions {
        let link = format!("https://leetcode.com/problems/{}/description", q.title_slug);
        let title = format!("[{}]({})", q.title, link);
        md_table.push_str(&format!("| [ ] | {} |\n", title));
    }

    fs::write("medium.md", md_table).unwrap();
}