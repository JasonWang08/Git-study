# 第一步：数据预处理
import pandas as pd
import re
import jieba
from sklearn.model_selection import train_test_split
import torch

# 加载清洗后的数据集
file_path = 'D:/nlp/clean_data.xlsx'
data = pd.read_excel(file_path)

# 使用 jieba 进行分词，同时处理可能的非字符串值
def tokenize_text(text):
    if pd.isna(text):
        return ''
    return ' '.join(jieba.lcut(str(text)))

data['TOKENIZED_TEXT'] = data['PADCONTENTXML_CLEANED'].apply(tokenize_text)

# 第二步：数据集划分
# 将数据集划分为训练集（80%）、验证集（10%）和测试集（10%）
train_data, temp_data = train_test_split(data, test_size=0.2, random_state=42)
val_data, test_data = train_test_split(temp_data, test_size=0.5, random_state=42)

# 保存划分后的数据集
train_data.to_excel('D:/nlp/train_data.xlsx', index=False)
val_data.to_excel('D:/nlp/val_data.xlsx', index=False)
test_data.to_excel('D:/nlp/test_data.xlsx', index=False)

# 第三步：使用 BERT 进行临床事件抽取
from transformers import BertTokenizer, BertForTokenClassification, Trainer, TrainingArguments
from torch.utils.data import Dataset, DataLoader

# 定义自定义数据集类
class ClinicalDataset(Dataset):
    def __init__(self, texts, labels, tokenizer, max_length):
        self.texts = texts
        self.labels = labels
        self.tokenizer = tokenizer
        self.max_length = max_length

    def __len__(self):
        return len(self.texts)

    def __getitem__(self, idx):
        text = self.texts[idx]
        encoding = self.tokenizer(
            text,
            add_special_tokens=True,
            truncation=True,
            max_length=self.max_length,
            padding='max_length',
            return_tensors='pt'
        )
        # 为简单起见，这里使用虚拟标签
        labels = torch.zeros(self.max_length, dtype=torch.long)
        return {
            'input_ids': encoding['input_ids'].flatten(),
            'attention_mask': encoding['attention_mask'].flatten(),
            'labels': labels
        }

# 加载预训练的 BERT 分词器
tokenizer = BertTokenizer.from_pretrained('bert-base-chinese')

# 准备训练数据集
train_texts = train_data['TOKENIZED_TEXT'].tolist()
val_texts = val_data['TOKENIZED_TEXT'].tolist()

train_dataset = ClinicalDataset(train_texts, None, tokenizer, max_length=128)
val_dataset = ClinicalDataset(val_texts, None, tokenizer, max_length=128)

# 加载预训练的 BERT 模型用于标注分类
model = BertForTokenClassification.from_pretrained('bert-base-chinese', num_labels=2)  # 二分类：相关与不相关

# 将模型移动到 GPU 上
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
model.to(device)

# 定义训练参数
training_args = TrainingArguments(
    output_dir='D:/nlp/bert_clinical_extraction',
    num_train_epochs=3,
    per_device_train_batch_size=8,
    per_device_eval_batch_size=8,
    evaluation_strategy='epoch',
    save_total_limit=2,
    logging_dir='D:/nlp/logs',
    logging_steps=10,
    fp16=True  # 启用混合精度训练以加速 GPU 训练
)

# 定义 Trainer
trainer = Trainer(
    model=model,
    args=training_args,
    train_dataset=train_dataset,
    eval_dataset=val_dataset,
    tokenizer=tokenizer,
    data_collator=lambda data: {
        'input_ids': torch.stack([f['input_ids'] for f in data]).to(device),
        'attention_mask': torch.stack([f['attention_mask'] for f in data]).to(device),
        'labels': torch.stack([f['labels'] for f in data]).to(device)
    }
)

# 训练模型
#trainer.train()

# 第四步：评价指标
from sklearn.metrics import classification_report

# 虚拟预测和标签用于评估（仅作演示用途）
y_true = [0, 1, 0, 1, 1, 0]
y_pred = [0, 1, 0, 0, 1, 1]

# 计算评价指标
report = classification_report(y_true, y_pred, target_names=['Not Relevant', 'Relevant'])
print(report)

# 第五步：保存训练好的模型
model.save_pretrained('D:/nlp/bert_clinical_extraction_model')
tokenizer.save_pretrained('D:/nlp/bert_clinical_extraction_tokenizer')